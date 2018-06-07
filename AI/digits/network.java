import java.util.*;
import java.io.*;
import java.awt.*;

public class network {
    public int num_layers;
    public ArrayList<Integer> sizes;
    matrix[] biases;
    matrix[] weights;
    public network(ArrayList<Integer> sizes) {
        Random r = new Random(12588512);
        this.num_layers = sizes.size();
        this.sizes = sizes;
        biases = new matrix[num_layers-1];
        for(int i = 0; i < num_layers-1; i++) {
            biases[i] = new matrix(sizes.get(i+1), 1);
            for(int j = 0; j < sizes.get(i+1); j++) {
                biases[i].mat[j][0] = r.nextGaussian();
            }
        }
        weights = new matrix[num_layers-1];
        for(int i = 0; i < num_layers-1; i++) {
            weights[i] = new matrix(sizes.get(i+1), sizes.get(i));
            for(int j = 0; j < sizes.get(i+1); j++) {
                for(int k = 0; k < sizes.get(i); k++) {
                    weights[i].mat[j][k] = r.nextGaussian();
                }
            }
        }
    }
    public matrix feedforward(matrix a) {
        matrix res = new matrix(a);
        for(int i = 0; i < num_layers-1; i++) {
            res = weights[i].times(res);
            res = biases[i].plus(res);
            res = tool.sigmoid(res);
        }
        return res;
    }
    public pairvmat backprop(matrix x, matrix y) { // x is input, y is desired output, computes dC/dz
        // feed forward and store activations
        matrix curAct = new matrix(x.N, 1);
        for(int i = 0; i < x.N; i++) curAct.mat[i][0] = x.mat[i][0];
        ArrayList<matrix> activations = new ArrayList<matrix>(); activations.add(curAct);
        ArrayList<matrix> zs = new ArrayList<matrix>();
        for(int i = 0; i < num_layers-1; i++) {
            matrix z = weights[i].times(curAct).plus(biases[i]);
            zs.add(z);
            curAct = tool.sigmoid(z);
            activations.add(curAct);
        }
        // errors of output layers
        matrix delta = tool.costprime(activations.get(activations.size()-1), y);
        delta = delta.hadamardmult(tool.sigmoidprime(zs.get(zs.size()-1)));
        // back prop
        matrix[] nabla_b = new matrix[num_layers-1];
        matrix[] nabla_w = new matrix[num_layers-1];
        for(int i = 0; i < num_layers-1; i++) {
            nabla_b[i] = new matrix(sizes.get(i+1), 1);
            nabla_w[i] = new matrix(sizes.get(i+1), sizes.get(i));
        }
        nabla_b[nabla_b.length-1] = new matrix(delta);
        nabla_w[nabla_w.length-1] = new matrix(delta.times(activations.get(activations.size()-2).transpose()));
        for(int l = 2; l < num_layers; l++) {
            matrix z = new matrix(zs.get(tool.ind(zs.size(), -l)));
            matrix sp = tool.sigmoidprime(z);
            delta = weights[tool.ind(weights.length, -l+1)].transpose().times(delta).hadamardmult(sp);
            nabla_b[tool.ind(nabla_b.length, -l)] = new matrix(delta);
            nabla_w[tool.ind(nabla_w.length, -l)] = delta.times(activations.get(tool.ind(activations.size(), -l-1)).transpose());
        }
        return new pairvmat(nabla_b, nabla_w);
    }
    public void update_mini_batch(pairmat[] mini_batch, double eta) {
        matrix[] dbiases = new matrix[num_layers-1];
        matrix[] dweights = new matrix[num_layers-1];
        for(int i = 0; i < num_layers-1; i++) {
            dbiases[i] = new matrix(sizes.get(i+1), 1);
            dweights[i] = new matrix(sizes.get(i+1), sizes.get(i));
        }
        for(pairmat p: mini_batch) {
            pairvmat pv = new pairvmat(backprop(p.F, p.S));
            for(int i = 0; i < num_layers-1; i++) dbiases[i] = dbiases[i].plus(pv.F[i]);
            for(int i = 0; i < num_layers-1; i++) dweights[i] = dweights[i].plus(pv.S[i]);
        }
        for(int i = 0; i < num_layers-1; i++) biases[i] = biases[i].plus(dbiases[i].times(-eta/(double)mini_batch.length));
        for(int i = 0; i < num_layers-1; i++) weights[i] = weights[i].plus(dweights[i].times(-eta/(double)mini_batch.length));
    }
    public void SGD(ArrayList<pairmat> training_data, int epochs, int mini_batch_size, double eta) {
        int n = training_data.size();
        for(int i = 0; i < epochs; i++) {
            Collections.shuffle(training_data);
            pairmat[] mini_batch = new pairmat[mini_batch_size];
            for(int j = 0; j+mini_batch_size-1 < n; j += mini_batch_size) {
                for(int k = 0; k < mini_batch_size; k++) {
                    mini_batch[k] = new pairmat(training_data.get(j+k));
                }
                update_mini_batch(mini_batch, eta);
            }
            System.out.println("Epoch " + Integer.toString(i) + " complete");
            double count = 0;
            for(int j = 0; j < 500; j++) {
                matrix res = new matrix(feedforward(training_data.get(j).F));
                int mx = 0;
                int ans = 0;
                for(int k = 0; k < 10; k++) {
                    if(training_data.get(j).S.mat[k][0] > 0.5) ans = k;
                    if(res.mat[k][0] > res.mat[mx][0]) mx = k;
                }
                if(mx == ans) count += 1.0;
            }
            System.out.println(count/5.0 + "% correct");
        }
    }
}
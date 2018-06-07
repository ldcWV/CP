import java.io.*;
import java.util.*;
public class driver
{
    public static void main(String[] args) throws IOException {
        ArrayList<Integer> sizes = new ArrayList<Integer>();
        sizes.add(784); sizes.add(30); sizes.add(10);
        network nn = new network(sizes);
        BufferedReader f = new BufferedReader(new FileReader("cnt.txt"));
        int cnt = Integer.parseInt(f.readLine());
        ArrayList<pairmat> data = new ArrayList<pairmat>();
        for(int i = 2000; i < 8000; i++) {
            matrix input = new matrix(784, 1);
            matrix output = new matrix(10, 1);
            f = new BufferedReader(new FileReader(tool.getFileName(i)));
            StringTokenizer st = new StringTokenizer(f.readLine());
            output.mat[Integer.parseInt(st.nextToken())][0] = 1;
            for(int j = 0; j < 784; j++) input.mat[j][0] = Integer.parseInt(st.nextToken());
            data.add(new pairmat(input, output));
            if(i%10 == 0) System.out.println("case " + i + " uploaded");
        }
        nn.SGD(data, 90, 15, .05);
        double success = 0;
        for(int i = 8000; i < 15000; i++) {
            matrix input = new matrix(784, 1);
            f = new BufferedReader(new FileReader(tool.getFileName(i)));
            StringTokenizer st = new StringTokenizer(f.readLine());
            int k = Integer.parseInt(st.nextToken());
            for(int j = 0; j < 784; j++) input.mat[j][0] = Integer.parseInt(st.nextToken());
            matrix output = nn.feedforward(input);
            int mx = 0;
            for(int j = 0; j < 10; j++) {
                if(output.mat[j][0] > output.mat[mx][0]) mx = j;
            }
            if(mx == k) success += 1.0;
            tool.draw(i);
            System.out.print("Guess: " + mx + ", accuracy = ");
            StdDraw.clear();
            System.out.println(100.0*(success/(i-7999.0)) + "%");
            StdDraw.pause(1000);
        }
        System.out.println(success + "/" + "7000");
    }
}

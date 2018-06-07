import java.util.*;
import java.io.*;
import java.awt.*;

public class tool
{
    public static String getFileName(int k) {
        return "cases/" + Integer.toString(k) + ".txt";
    }
    public static void setFile(PrintWriter w, String s) throws IOException {
        w = new PrintWriter(new FileWriter(s));
    }
    public static void draw(int ind) throws IOException {
        StdDraw.setXscale(0, 28);
        StdDraw.setYscale(0, 28);
        BufferedReader f = new BufferedReader(new FileReader(getFileName(ind)));
        sample s = new sample(f.readLine());
        System.out.println(s.ans);
        s.draw();
    }
    public static double sigmoid(double z) {
        return 1.0/(1.0+Math.exp(-z));
    }
    public static matrix sigmoid(matrix z) {
        matrix ans = new matrix(z);
        for(int i = 0; i < z.N; i++) {
            for(int j = 0; j < z.M; j++) {
                ans.mat[i][j] = sigmoid(ans.mat[i][j]);
            }
        }
        return ans;
    }
    public static double sigmoidprime(double z) {
        return sigmoid(z)*(1-sigmoid(z));
    }
    public static matrix sigmoidprime(matrix z) {
        matrix ans = new matrix(z);
        for(int i = 0; i < z.N; i++) {
            for(int j = 0; j < z.M; j++) {
                ans.mat[i][j] = sigmoidprime(ans.mat[i][j]);
            }
        }
        return ans;
    }
    public static double costprime(double a, double y) {
        return a-y;
    }
    public static matrix costprime(matrix a, matrix y) {
        return a.plus(y.times(-1.0));
    }
    public static int ind(int n, int i) {
        return (n+(i%n))%n;
    }
    public static int getCnt() throws IOException {
        BufferedReader f = new BufferedReader(new FileReader("cnt.txt"));
        int cnt = Integer.parseInt(f.readLine()); f.close();
        return cnt;
    }
    public static void incCnt() throws IOException {
        int cnt = getCnt();
        PrintWriter cntp = new PrintWriter(new BufferedWriter(new FileWriter("cnt.txt")));
        cntp.print(cnt+1);
        cntp.close();
    }
}

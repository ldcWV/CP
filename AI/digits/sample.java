import java.util.*;
import java.io.*;
import java.awt.*;

public class sample
{
    public int ans;
    public int[] vals;
    public sample(String s) {
        StringTokenizer st = new StringTokenizer(s);
        ans = Integer.parseInt(st.nextToken());
        vals = new int[784];
        for(int i = 0; i < 784; i++) {
            vals[i] = Integer.parseInt(st.nextToken());
        }
    }
    public sample(int k) {
        ans = k;
        vals = new int[784];
    }
    public void draw() {
        for(int i = 0; i < 28; i++) {
            for(int j = 0; j < 28; j++) {
                int gr = 255-vals[28*i+j];
                StdDraw.setPenColor(new Color(gr, gr, gr));
                StdDraw.filledRectangle(i+0.5, j+0.5, 0.5, 0.5);
            }
        }
    }
    public void paint(int x, int y, int s) {
        if(x*28+y >= 0 && x*28+y < 784) {
            vals[x*28+y] += s;
            vals[x*28+y] = Math.min(vals[x*28+y], 255);
            int gr = 255-vals[28*x+y];
            StdDraw.setPenColor(new Color(gr, gr, gr));
            StdDraw.filledRectangle(x+0.5, y+0.5, 0.5, 0.5);
        }
    }
    public String toString() {
        StringBuilder res = new StringBuilder(1569);
        res.append(ans);
        for(int i = 0; i < 784; i++) {
            res.append(" ");
            res.append(vals[i]);
        }
        return res.toString();
    }
}

import java.io.*;
import java.util.*;

public class addSamples
{
    public static void main(String[] args) throws IOException {
        StdDraw.setXscale(0, 28);
        StdDraw.setYscale(0, 28);
        Scanner sc = new Scanner(System.in);
        int cnt = tool.getCnt();
        int w = sc.nextInt();
        for(int j = 0; j < w; j++) {
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.filledRectangle(2, 2, 2, 2);
            int k = (int)(Math.random()*10.0);
            StdDraw.setPenColor(StdDraw.WHITE);
            StdDraw.text(2, 2, Integer.toString(k));
            PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(tool.getFileName(cnt))));
            sample s = new sample(k);
            int px = -1;
            int py = -1;
            StdDraw.pause(400);
            while(true) {
                if(StdDraw.isMousePressed()) {
                    double x = StdDraw.mouseX();
                    double y = StdDraw.mouseY();
                    if(x <= 4 && y <= 4 && x >= 0 && y >= 0) break;
                    int ix = (int)x;
                    int iy = (int)y;
                    if(ix == px && iy == py) continue;
                    px = ix;
                    py = iy;
                    int g0 = 200, g1 = 120, g2 = 50;
                    s.paint(ix, iy, g0);
                    s.paint(ix-1, iy, g1); s.paint(ix+1, iy, g1); s.paint(ix, iy-1, g1); s.paint(ix, iy+1, g1);
                    s.paint(ix-1, iy-1, g2); s.paint(ix-1, iy+1, g2); s.paint(ix+1, iy-1, g2); s.paint(ix+1, iy+1, g2);
                }
            }
            out.print(s);
            out.close();
            tool.incCnt();
            StdDraw.clear();
        }
    }
}

import java.io.*;
import java.util.*;

public class test
{
    public static void main(String[] args) throws IOException {
        for(int i = 0; i < 400; i++) {
            tool.draw(i);
            StdDraw.pause(1000);
        }
    }
}

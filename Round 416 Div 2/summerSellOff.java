import java.util.*;
import java.io.*;
public class summerSellOff
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        StringTokenizer st = new StringTokenizer(sc.nextLine());
        int numDays = Integer.parseInt(st.nextToken());
        int numSellOuts = Integer.parseInt(st.nextToken());
        int[][] info = new int[numDays][2];
        for(int i = 0; i<numDays; i++)
        {
            st = new StringTokenizer(sc.nextLine());
            info[i][0]=Integer.parseInt(st.nextToken());
            info[i][1]=Integer.parseInt(st.nextToken());
        }
        long[] profit = new long[numDays]; //profit[i] means profit gained by doubling sales on that day
        for(int i = 0; i<numDays; i++)
        {
            profit[i]=Math.min(2*info[i][0],info[i][1])-Math.min(info[i][0],info[i][1]);
        }
        long sum = 0;
        for(int i = 0; i<numDays; i++)
        {
            sum+=Math.min(info[i][0],info[i][1]);
        }
        Arrays.sort(profit);
        for(int i = numDays-numSellOuts; i<numDays; i++)
        {
            sum+=profit[i];
        }
        System.out.println(sum);
    }
}

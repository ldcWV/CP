import java.util.*;
import java.io.*;
public class doyouwantadate
{
    public static long mod = (long)Math.pow(10,9)+7;
    public static long powMod(long b) //2^a % mod
    {
        long a1 = 2;
        long p = 1;
        while(b>0)
        {
            if(b%2==1)
            {
                p*=a1;
                p=p%mod;
            }
            b/=2;
            a1=(a1*a1)%mod;
        }
        return p;
    }
    public static long mod(long a)
    {
        while(a<0)
        {
            a+=mod;
        }
        return a%mod;
    }
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int numHacked = Integer.parseInt(sc.nextLine());
        StringTokenizer st = new StringTokenizer(sc.nextLine());
        long[] positions = new long[numHacked];
        for(int i = 0; i<numHacked; i++)
        {
            positions[i]=Long.parseLong(st.nextToken());
        }
        Arrays.sort(positions);
        long sum = 0;
        for(int i = 0; i<numHacked; i++)
        {
            sum+=(positions[i]*(powMod(i)-1))%mod;
            sum-=(positions[i]*(powMod(numHacked-i-1)-1))%mod;
        }
        sum = mod(sum);
        System.out.println(sum);
    }
}

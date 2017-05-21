import java.util.*;
import java.lang.*;
import java.io.*;

public class straightA
{
	public static int round(double a)
	{
		return ((int)(a+0.5));
	}
	public static void main (String[] args)
	{
		Scanner sc = new Scanner(System.in);
		StringTokenizer st = new StringTokenizer(sc.nextLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		double sum = 0;
		st = new StringTokenizer(sc.nextLine());
		for(int i = 0; i<n; i++)
		{
			sum+=Integer.parseInt(st.nextToken());
		}
		int i = 0;
		while(true)
		{
			if(round((sum+i*k)/(double)(n+i))==k)
			{
				System.out.println(i);
				break;
			}
			i++;
		}
	}
}
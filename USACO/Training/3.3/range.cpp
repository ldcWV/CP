/*
 ID: ldorian1
 LANG: C++11
 TASK: range
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <queue>
#include <set>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

const int MAX_N=250;

bool good[MAX_N][MAX_N]; //good[i][j] determines whether square at (i,j) is edible
bool good1[MAX_N][MAX_N];

int main()
{
	//READING INPUT
    ofstream fout("range.out");
    ifstream fin("range.in");
    int n; fin >> n;
    int a[n][n];
    F0R(i, n)
    {
    	string s; fin >> s;
    	F0R(j, n)
    	{
    		a[i][j]=stoi(s.substr(j,1));
    	}
    }
    int ans[n+1]; F0R(i, n+1) ans[i]=0;
    
    
    //SETTING UP SQUARES OF SIDE 1
    F0R(i, n) F0R(j, n) if(a[i][j]==1)
    {
    	good[i][j]=true;
    }
    //MAIN ALGORITHM
    FOR(side, 2, n+1)
    {
    	F0R(i, n-side+1) F0R(j, n-side+1)
    	{
    		if(good[i][j]&&good[i+1][j]&&good[i][j+1]&&good[i+1][j+1])
    		{
    			good1[i][j]=true;
    			ans[side]++;
    		}
    	}
    	F0R(i, n) F0R(j, n)
    	{
    		good[i][j]=good1[i][j];
    		good1[i][j]=false;
    	}
    }
    FOR(i, 2, n+1) if(ans[i]!=0) fout << i << " " << ans[i] << endl;
}
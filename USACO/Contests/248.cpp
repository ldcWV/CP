/*
 ID: ldorian1
 LANG: C++11
 TASK:
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
#include <stack>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

int dp[248][248]; //dp[i][j] is number if [i,j] can be combined, -1 otherwise
int n;
int nums[248];

int f(int start, int end)
{
    if(dp[start][end]!=-2) return dp[start][end];
    FOR(i, start, end)
    {
        if(f(start,i)!=-1 && f(i+1,end)!=-1 && dp[start][i]==dp[i+1][end])
        {
            dp[start][end]=dp[start][i]+1;
            return dp[start][end];
        }
    }
    dp[start][end]=-1;
    return -1;
}

int main()
{
    ofstream fout("248.out");
    ifstream fin("248.in");
    fin >> n;
    F0R(i, n) fin >> nums[i];
    F0R(i, n) F0R(j, n) dp[i][j]=-2;
    F0R(i, n) dp[i][i]=nums[i];
    int currMax=0;
    f(0, n-1);
    F0R(i, n)
    {
        F0R(j, n)
        {
            if(dp[i][j]>currMax) currMax=dp[i][j];
            //cout<<dp[i][j]<<" ";
        }
        //cout << endl;
    }
    fout << currMax << endl;
}

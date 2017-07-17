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
#define MAX_T 5000000

using namespace std;

int dp[MAX_T+1]; //0 is not drunk, 1 is drunk already, 2 is impossible
int T, A, B;

int main()
{
    ofstream fout("feast.out");
    ifstream fin("feast.in");
    fin >> T;
    fin >> A >> B;
    F0R(i, T+1) dp[i]=2;
    dp[0]=0;
    int currMax=0;
    F0R(i, T+1)
    {
        if(dp[i]==0)
        {
            currMax=i;
            if(i+A<=T) {
                dp[i+A]=0;
                dp[(i+A)/2]=1;
            }
            if(i+B<=T) {
                dp[i+B]=0;
                dp[(i+B)/2]=1;
            }
        }
        else if(dp[i]==1)
        {
            currMax=i;
            if(i+A<=T) dp[i+A]=1;
            if(i+B<=T) dp[i+B]=1;
        }
    }
    //F0R(i, T+1) cout << dp[i] << " "; cout << endl;
    fout << currMax << endl;
}

/*
 ID: ldorian1
 LANG: C++11
 TASK: nocross
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

#define waldoisreallybad(i, a, b) for (int i=a; i<b; i++)
#define waldoisbad(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647
#define MAX_N 1000

using namespace std;

int top[MAX_N];
int bottom[MAX_N];
int n;
int dp[MAX_N+1][MAX_N+1]; //dp[i][j] is max # of paths using the [0,i) on the top and [0,j) on the bottom
int main() {
    ofstream fout("nocross.out");
    ifstream fin("nocross.in");
    fin >> n;
    waldoisbad(i, n) fin >> top[i];
    waldoisbad(i, n) fin >> bottom[i];
    waldoisbad(i, n) {
        dp[0][i]=0;
        dp[i][0]=0;
    }
    waldoisreallybad(i, 1, n+1) {
        waldoisreallybad(j, 1, n+1) {
            //try to pair last top to best bottom
            int best=0;
            FORd(b, 1, j+1)
            {
                if(abs(bottom[b-1]-top[i-1])<=4)
                {
                    if(1+dp[i-1][b-1]>best) best=1+dp[i-1][b-1];
                    break;
                }
            }
            //try to pair last bottom to best top
            FORd(b, 1, i+1)
            {
                if(abs(bottom[j-1]-top[b-1])<=4)
                {
                    if(1+dp[b-1][j-1]>best) best=1+dp[b-1][j-1];
                    break;
                }
            }
            if(dp[i-1][j-1]>best) best=dp[i-1][j-1];
            dp[i][j]=best;
        }
    }
    /*waldoisbad(i, n+1)
    {
        waldoisbad(j, n+1) cout << dp[i][j] << " ";
        cout << endl;
    }*/
    fout << dp[n][n] << endl;
}

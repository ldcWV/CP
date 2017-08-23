/*
 ID: ldorian1
 LANG: C++11
 TASK: hps
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
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)


#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 100000
#define MAX_K 21

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, k;
int dp[MAX_N][MAX_K][3];
int arr[MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("hps.out");
    ifstream fin("hps.in");
    fin >> n >> k; k++;
    F0R(i, n) {
        string a; fin >> a;
        if(a=="H") arr[i]=0;
        else if(a=="P") arr[i]=1;
        else arr[i]=2;
    }
    
    dp[0][0][arr[0]]=1;
    FOR(i, 1, k) {
        dp[0][i][0]=1;
        dp[0][i][1]=1;
        dp[0][i][2]=1;
    }
    FOR(i, 1, n) {
        dp[i][0][0]=dp[i-1][0][0];
        dp[i][0][1]=dp[i-1][0][1];
        dp[i][0][2]=dp[i-1][0][2];
        dp[i][0][arr[i]]++;
    }
    
    FOR(i, 1, n) {
        int c = arr[i];
        //if no change
        FOR(j, 1, k) {
            dp[i][j][0]=dp[i-1][j][0];
            dp[i][j][1]=dp[i-1][j][1];
            dp[i][j][2]=dp[i-1][j][2];
            dp[i][j][c]++;
        }
        //if change
        FOR(j, 1, k) {
            dp[i][j][c]=max(dp[i][j][c], max(dp[i-1][j-1][0]+1, max(dp[i-1][j-1][1]+1, dp[i-1][j-1][2]+1)));
        }
    }
    
    int hi = 0;
    F0R(j, k) hi=max(hi, max(dp[n-1][j][0], max(dp[n-1][j][1], dp[n-1][j][2])));
    fout << hi << "\n";
}

/*
 ID: ldorian1
 LANG: C++11
 TASK: palpath
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
#include <map>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a)+(b))%(b))

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 500

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
char arr[MAX_N][MAX_N];
int dp[2][MAX_N][MAX_N];
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("palpath.out");
    ifstream fin("palpath.in");
    
    fin >> n;
    F0R(i, n) F0R(j, n) fin >> arr[i][j];
    F0R(i, n) F0R(j, n) { //calculate dp[0][i][j]
        dp[0][i][j] = (i == j);
    }
    FOR(l, 1, n) { //calculate dp[l][x][y] for all x and y
        int prev = (l - 1) % 2;
        int d = l % 2;
        F0R(i, n - l) FOR(j, l, n) {
            int ai = i;
            int aj = n - l - i - 1;
            int bi = j;
            int bj = n + l - j - 1;
            if(arr[ai][aj] != arr[bi][bj]) {
                dp[d][i][j] = 0;
                continue;
            }
            dp[d][i][j] = dp[prev][i][j];
            dp[d][i][j] = dp[d][i][j] % MOD;
            
            dp[d][i][j] += dp[prev][i+1][j];
            dp[d][i][j] = dp[d][i][j] % MOD;
            
            dp[d][i][j] += dp[prev][i][j-1];
            dp[d][i][j] = dp[d][i][j] % MOD;
            
            dp[d][i][j] += dp[prev][i+1][j-1];
            dp[d][i][j] = dp[d][i][j] % MOD;
        }
    }
    fout << dp[(n+1)%2][0][n-1] << "\n";
}

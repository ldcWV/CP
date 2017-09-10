/*
 ID: ldorian1
 LANG: C++11
 TASK: team
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
#define MAX_N 1000
#define MAX_K 10
#define MOD 1000000009

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

ll arr0[MAX_N];
ll arr1[MAX_N];

int n, m, k;

ll dp[MAX_N+1][MAX_N+1][MAX_K+1];

ll f(int a, int b, int c) {
    if(arr0[a]<=arr1[b]) return 0;
    return dp[a][b][c];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("team.out");
    ifstream fin("team.in");
    fin >> n >> m >> k;
    F0R(i, n) fin >> arr0[i];
    F0R(i, m) fin >> arr1[i];
    
    sort(begin(arr0), begin(arr0)+n);
    sort(begin(arr1), begin(arr1)+m);
    
    F0R(i, m+1) F0R(j, k+1) dp[0][i][j]=0;
    F0R(i, n+1) F0R(j, k+1) dp[i][0][j]=0;
    F0R(i, n+1) F0R(j, m+1) dp[i][j][0]=1;
    FOR(c, 1, k+1) {
        FOR(a, 1, n+1) {
            FOR(b, 1, m+1) {
                dp[a][b][c]=(dp[a-1][b][c]+dp[a][b-1][c]+f(a-1,b-1,c-1)-dp[a-1][b-1][c]+MOD)%MOD;
            }
        }
    }
    fout << dp[n][m][k] << endl;
}

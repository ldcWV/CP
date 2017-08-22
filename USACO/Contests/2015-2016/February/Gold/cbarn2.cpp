/*
 ID: ldorian1
 LANG: C++11
 TASK: cbarn2
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

#define MAX_N 100
#define MAX_K 7

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, k;
ll dp[MAX_N][MAX_K];
ll value[MAX_N+1][MAX_N+1];
int arr[MAX_N];

ll v(int a, int b, int st) {
    if(value[a][b]!=-1) return value[a][b];
    ll s = 0;
    FOR(i, a, b) s+=arr[(i+st)%n]*(i-a);
    value[a][b]=s;
    return s;
}

ll solve(int a, int b, int st) {
    if(dp[a][b]!=-1) return dp[a][b];
    ll m = 10000000000;
    FOR(i, a+1, n) {
        m = min(m, v(a, i, st)+solve(i, b-1, st));
    }
    dp[a][b]=m;
    return m;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("cbarn2.out");
    ifstream fin("cbarn2.in");
    fin >> n >> k;
    F0R(j, n+1) F0R(l, n+1) value[j][l]=-1;
    F0R(i, n) fin >> arr[i];
    ll m = 10000000000;
    F0R(i, n) {
        F0R(j, n+1) F0R(l, n+1) value[j][l]=-1;
        F0R(j, n) F0R(l, k) dp[j][l]=-1;
        F0R(j, k) dp[n-1][j]=0;
        F0R(j, n) dp[j][0]=v(j, n, i);
        m=min(m,solve(0, k-1, i));
    }
    fout << m << endl;
}

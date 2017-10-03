/*
 ID: ldorian1
 LANG: C++11
 TASK: nochange
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

#define MAX_N 100000
#define MAX_K 16

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, k;
ll needed[MAX_N];
ll coins[MAX_K];
int dp[1<<MAX_K];
ll cost[1<<MAX_K];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("nochange.out");
    ifstream fin("nochange.in");
    fin >> k >> n;
    F0R(i, k) fin >> coins[i];
    fin >> needed[0];
    FOR(i, 1, n) {
        fin >> needed[i];
        needed[i]+=needed[i-1];
    }
    F0R(i, 1<<k) dp[i]=-1;
    F0R(i, k) {
        dp[1 << i] = (int)(upper_bound(begin(needed), begin(needed)+n, coins[i])-begin(needed))-1;
    }
    cost[0]=0;
    FOR(i, 1, 1<<k) {
        cost[i] = cost[i-(1<<__builtin_ctz(i))]+coins[__builtin_ctz(i)];
    }
    
    ll hi = -1;
    FOR(i, 1, 1<<k) {
        if(dp[i]==n-1) {
            hi = max(hi, cost[i^((1<<k)-1)]);
            continue;
        }
        if(dp[i]!=-1) continue;
        F0R(j, k) if(i & (1<<j)) {
            int r = i - (1<<j);
            ll have = needed[dp[r]];
            dp[i] = max(dp[i], (int)(upper_bound(begin(needed), begin(needed)+n, have+coins[j])-begin(needed))-1);
        }
        if(dp[i]==n-1) hi = max(hi, cost[i^((1<<k)-1)]);
    }
    fout << hi << "\n";
}

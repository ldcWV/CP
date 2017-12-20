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
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;

const ll MOD = 1000000007;
const int MAX_N = 100000;
ll dp[MAX_N][3]; //number of ways to color subtree given that node is predetermined color
vi adj[MAX_N];
int n, k;

int color[MAX_N];
vi child[MAX_N];
bool vis[MAX_N];

void dfs(int u) {
    vis[u] = 1;
    for(int v: adj[u]) if(!vis[v]) {
        dfs(v);
        child[u].PB(v);
    }
}

ll solve(int u, int parcolor) {
    if(parcolor != -1 && dp[u][parcolor] != -1) return dp[u][parcolor];
    if(color[u] != -1) {
        if(parcolor == color[u]) return 0;
        ll ans = 1;
        for(int v: child[u]) {
            ans *= solve(v, color[u]);
            ans %= MOD;
        }
        if(parcolor != -1) dp[u][parcolor] = ans;
        return ans;
    }
    ll ans = 0;
    M00(i, 3) if(i != parcolor) {
        ll temp = 1;
        for(int v: child[u]) {
            temp *= solve(v, i);
            temp %= MOD;
        }
        ans += temp;
        ans %= MOD;
    }
    if(parcolor != -1) dp[u][parcolor] = ans;
    return ans;
}

int main() { FAST
    ofstream fout("barnpainting.out");
    ifstream fin("barnpainting.in");
    fin >> n >> k;
    M00(i, n-1) {
        int a, b; fin >> a >> b;
        a--; b--;
        adj[a].PB(b);
        adj[b].PB(a);
    }
    dfs(0);
    M00(i, n) color[i] = -1;
    M00(i, k) {
        int a, b;
        fin >> a >> b;
        a--; b--;
        color[a] = b;
    }
    M00(i, n) M00(j, 3) dp[i][j] = -1;
    fout << solve(0, -1) << "\n";
}

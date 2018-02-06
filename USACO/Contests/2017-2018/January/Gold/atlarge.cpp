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

template<int SZ> struct tree {
    vector<pair<int, int>> adj[SZ];
    const static int LGSZ = 32-__builtin_clz(SZ-1);
    pair<int, int> ppar[SZ][LGSZ];
    vi child[SZ];
    int depth[SZ];
    int distfromroot[SZ];
    bool highest[SZ];
    int root;
    int realsz;
    
    void addEdge(int u, int v, int d) {
        adj[u].PB(MP(v, d));
        adj[v].PB(MP(u, d));
    }
    void dfs(int u, int dep, ll dis) {
        depth[u] = dep;
        distfromroot[u] = dis;
        for(auto& v: adj[u]) if(ppar[u][0].F != v.F) {
            ppar[v.F][0] = MP(u, v.S);
            dfs(v.F, dep + 1, dis + v.S);
        }
    }
    void build(int r, int x) { // r is the root
        realsz = x;
        root = r;
        ppar[r][0] = MP(r, 0);
        M00(i, realsz) depth[i] = 0;
        dfs(r, 0, 0);
        MOO(i, 1, LGSZ) M00(j, realsz) {
            ppar[j][i].F = ppar[ppar[j][i-1].F][i-1].F;
            ppar[j][i].S = ppar[j][i-1].S + ppar[ppar[j][i-1].F][i-1].S;
        }
        M00(i, realsz) {
            child[i].clear();
        }
        M00(i, realsz) if(i != r) {
            child[ppar[i][0].F].PB(i);
        }
        M00(i, realsz) highest[i] = false;
    }
    int lca(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);
        M00d(i, LGSZ) if(depth[ppar[u][i].F] >= depth[v]) u = ppar[u][i].F;
        if(u == v) return u;
        M00d(i, LGSZ) {
            if(ppar[u][i].F != ppar[v][i].F) {
                u = ppar[u][i].F;
                v = ppar[v][i].F;
            }
        }
        return ppar[u][0].F;
    }
    int dist(int u, int v) {
        return distfromroot[u] + distfromroot[v] - 2*distfromroot[lca(u, v)];
    }
    int kthpar(int u, int k) {
        //cout << root << ": " << u << " ";
        M00d(i, LGSZ) {
            if(k >= (1 << i)) {
                k -= (1 << i);
                u = ppar[u][i].F;
            }
        }
        //assert(k == 0);
        //cout << u << "\n";
        return u;
    }
    int dfs2(int u) {
        if(highest[u]) return 1;
        int ans = 0;
        for(int v: child[u]) ans += dfs2(v);
        return ans;
    }
    int getNeeded() {
        if(child[root].size() == 1) return 1; // on exit already
        M00(i, realsz) {
            if(child[i].size() == 0) { // for all exits, compute highest
                int dis = dist(i, root)/2;
                highest[kthpar(i, dis)] = true;
            }
        }
        return dfs2(root);
    }
};

const ll MOD = 1000000007;
const int MAX_N = 100000;
int n, k;

int main() { FAST
    ofstream fout("atlarge.out");
    ifstream fin("atlarge.in");
    tree<MAX_N> t;
    fin >> n >> k;
    M00(i, n-1) {
        int a, b; fin >> a >> b;
        a--; b--;
        t.addEdge(a, b, 1);
    }
    t.build(k-1, n); // root it here
    fout << t.getNeeded() << "\n";
}

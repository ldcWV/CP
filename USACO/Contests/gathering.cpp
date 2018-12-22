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
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <sstream>

using namespace std;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define all(v) v.begin(), v.end()

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << '\n', 0;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;

template<int SZ> struct tree {
    vector<pair<int, ll>> adj[SZ];
    const static int LGSZ = 32-__builtin_clz(SZ-1);
    pair<int, ll> ppar[SZ][LGSZ];
    int depth[SZ];
    ll distfromroot[SZ];
    
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
    void build() {
        ppar[0][0] = MP(0, 0);
        M00(i, SZ) depth[i] = 0;
        dfs(0, 0, 0);
        MOO(i, 1, LGSZ) M00(j, SZ) {
            ppar[j][i].F = ppar[ppar[j][i-1].F][i-1].F;
            ppar[j][i].S = ppar[j][i-1].S + ppar[ppar[j][i-1].F][i-1].S;
        }
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
    ll dist(int u, int v) {
        return distfromroot[u] + distfromroot[v] - 2*distfromroot[lca(u, v)];
    }
    bool insubtree(int u, int v) {
        return (lca(u,v) == v);
    }
};

const int MAX_N = 100005;
int n, m;
vi pre[MAX_N]; // need to do i before any of pre[i]
vi adj[MAX_N];
vi ch[MAX_N];
tree<MAX_N> T;
set<pi> bad; // {first, second}
bool res[MAX_N];

void setup(int u, int p) {
    for(int v: adj[u]) if(v != p) {
        ch[u].PB(v);
        setup(v, u);
    }
}

void dfs2(int u) {
    if(bad.empty()) {
        res[u] = 1;
    }
    for(int v: ch[u]) {
        // child became parent of everything
        for(int s: pre[v]) {
            bad.insert(MP(v,s));
        }
        // parent lost parentship of everything in the subtree of v
        for(int s: pre[u]) {
            if(bad.count(MP(u, s)) && T.insubtree(s, v)) {
                bad.erase(MP(u, s));
            }
        }
        dfs2(v);
        
        // child lost parentship of everything in its subtree
        for(int s: pre[v]) {
            if(!T.insubtree(s, v)) {
                bad.erase(MP(v, s));
            }
        }
        // parent is now parent of everything
        for(int s: pre[u]) {
            bad.insert(MP(u, s));
        }
    }
}

int deg[MAX_N];
bool mark[MAX_N];
int precnt[MAX_N];
vi to[MAX_N];

bool check() {
    queue<int> del;
    M00(i, n) if(deg[i] == 1 && precnt[i] == 0) del.push(i);
    int ctr = 0;
    while(!del.empty()) {
        int u = del.front();
        del.pop();
        if(mark[u]) continue;
        mark[u] = 1;
        for(int v: adj[u]) if(!mark[v]) {
            deg[v]--;
            if(deg[v] <= 1) {
                if(precnt[v] == 0) del.push(v);
            }
        }
        for(int v: pre[u]) if(!mark[v]) {
            precnt[v]--;
            if(deg[v] <= 1 && precnt[v] == 0) del.push(v);
        }
        ctr++;
    }
    if(ctr == n) return 1;
    return 0;
}

int main() { FAST
    freopen("gathering.in","r",stdin);
    freopen("gathering.out","w",stdout);
    cin >> n >> m;
    M00(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].PB(b);
        adj[b].PB(a);
        deg[a]++;
        deg[b]++;
        T.addEdge(a,b,1);
    }
    M00(i, m) {
        int a, b; cin >> a >> b;
        a--; b--;
        pre[a].PB(b);
        to[b].PB(a);
    }
    M00(i, n) precnt[i] = (int)to[i].size();
    T.build();
    setup(0, -1);
    
    if(!check()) {
        M00(i, n) cout << "0\n";
        return 0;
    }
    
    M00(u, n) {
        for(int v: pre[u]) {
            if(T.insubtree(v,u)) bad.insert(MP(u,v));
        }
    }
    dfs2(0);
    M00(i, n) cout << res[i] << "\n";
}

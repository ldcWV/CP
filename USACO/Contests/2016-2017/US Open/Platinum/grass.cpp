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
#include <assert.h>
#include <unordered_map>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a)+(b))%(b))

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

const ll MOD = 1000000007;

struct Edge {
    int len;
    int a, b;
    Edge(int a, int b, int l) {
        this->len = l;
        this->a = a;
        this->b = b;
    }
    bool operator<(const Edge& other) const {
        return (this->len < other.len);
    }
};

template<int SZ> struct DSU {
    int par[SZ];
    int size[SZ];
    DSU() {
        M00(i, SZ) par[i] = i, size[i] = 1;
    }
    int get(int node) {
        if(par[node] != node) par[node] = get(par[node]);
        return par[node];
    }
    bool connected(int n1, int n2) {
        return (get(n1) == get(n2));
    }
    void unite(int n1, int n2) {
        n1 = get(n1);
        n2 = get(n2);
        if(n1 == n2) return;
        if(rand()%2) {
            par[n1] = n2;
            size[n2] += size[n1];
        } else {
            par[n2] = n1;
            size[n1] += size[n2];
        }
    }
};

const int MAX_N = 200000;
int n, m, k, q;
vector<pair<int, ll>> adj[MAX_N];
int par[MAX_N];
bool vis[MAX_N];
pair<ll, int> vert[MAX_N];
unordered_map<int, set<pair<ll, int>>> whale[MAX_N]; //all children
set<pair<ll, int>> vomit[MAX_N]; //children of distinct colors
set<pair<ll, int>> best;

pair<ll, int> getClosest(int u) { //distance to child of different color
    if(vomit[u].size() == 0) return MP(-1, -1); //leaf
    if(vomit[u].size() == 1) { //if all children are same color
        auto val = *vomit[u].begin();
        if(val.S == vert[u].S) return MP(-1, -1); //all children are same color as parent
        return val; //all children are different color, so return min distance
    }
    //if closest is not the same color, return the distance
    auto it = vomit[u].begin();
    if((*it).S != vert[u].S) return (*it);
    //otherwise, return second best
    it++; return (*it);
}
void updColor(int u, int c) {
    int orig = vert[u].S;
    vert[u].S = c;
    if(par[u] != -1) { //if it's not the root of the tree
        vomit[par[u]].erase(*whale[par[u]][orig].begin());
        if(whale[par[u]].count(c)) vomit[par[u]].erase(*whale[par[u]][c].begin());
        if(orig != -1) {
            whale[par[u]][orig].erase(MP(vert[u].F, orig));
            if(whale[par[u]][orig].size() == 0) whale[par[u]].erase(orig);
        }
        whale[par[u]][c].insert(MP(vert[u].F, c));
        //update vomit
        if(orig != -1 && whale[par[u]].count(orig)) vomit[par[u]].insert(*whale[par[u]][orig].begin());
        vomit[par[u]].insert(*whale[par[u]][c].begin());
    }
}

void dfs(int u) {
    vis[u] = 1;
    for(auto v: adj[u]) if(!vis[v.F]) {
        vert[v.F].F = v.S;
        par[v.F] = u;
        dfs(v.F);
    }
}

int main() { FAST
    ofstream fout("grass.out");
    ifstream fin("grass.in");
    fin >> n >> m >> k >> q;
    M00(i, n) vert[i] = MP(-1, -1);
    vector<Edge> krus;
    M00(i, m) {
        int a, b, l; fin >> a >> b >> l;
        a--; b--;
        krus.PB(Edge(a, b, l));
    }
    sort(krus.begin(), krus.end());
    DSU<MAX_N> ds;
    M00(i, m) {
        if(!ds.connected(krus[i].a, krus[i].b)) {
            ds.unite(krus[i].a, krus[i].b);
            adj[krus[i].a].PB(MP(krus[i].b, krus[i].len));
            adj[krus[i].b].PB(MP(krus[i].a, krus[i].len));
        }
    }
    dfs(0); par[0] = -1;
    M00(i, n) {
        int c; fin >> c;
        updColor(i, c);
    }
    M00(i, n) {
        auto p = getClosest(i);
        if(p.F != -1) best.insert(p);
    }
    M00(i, q) {
        int u, co; fin >> u >> co; u--;
        auto p = getClosest(u);
        if(u != 0) {
            auto p2 = getClosest(par[u]);
            if(p2.F != -1) {
                assert(best.count(p2) > 0);
                best.erase(p2);
            }
        }
        if(p.F != -1) {
            //assert(best.count(p) > 0);
            best.erase(p);
        }
        updColor(u, co);
        auto q = getClosest(u);
        if(q.F != -1) best.insert(q);
        if(u != 0) {
            auto q2 = getClosest(par[u]);
            if(q2.F != -1) best.insert(q2);
        }
        fout << (*best.begin()).F << "\n";
    }
}

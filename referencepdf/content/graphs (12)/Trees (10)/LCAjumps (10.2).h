/**
 * Description: calculates least common ancestor in tree with binary jumping
 * Time: O(N\log N)
 * Source: USACO Camp
 * Verification: Debug the Bugs
 */

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
};

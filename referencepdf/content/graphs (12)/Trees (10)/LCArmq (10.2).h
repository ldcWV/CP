/**
 * Description: Euler Tour LCA w/ O(1) query
 * Source: own
 * Verification: USACO Debug the Bugs
 */

template<int SZ> struct tree {
    vector<pair<int, ll>> adj[SZ];
    pair<int, ll> par[SZ];
    const static int LGSZ = 33-__builtin_clz(SZ-1);
    ll distfromroot[SZ];
    int depth[SZ], t, tin[SZ], RMQ[2*SZ-1][LGSZ], oldToNew[SZ], newToOld[SZ], numNodes;
    
    void addEdge(int u, int v, int d) {
        adj[u].PB(MP(v, d));
        adj[v].PB(MP(u, d));
    }
    void dfs(int u, int dep, ll dis) {
        depth[u] = dep;
        distfromroot[u] = dis;
        for(auto& v: adj[u]) if(par[u].F != v.F) {
            par[v.F] = MP(u, v.S);
            dfs(v.F, dep + 1, dis + v.S);
        }
    }
    void buildtarr(int u) {
        RMQ[t][0] = oldToNew[u], tin[oldToNew[u]] = t++;
        for(auto& v: adj[u]) if(par[u].F != v.F) {
            buildtarr(v.F);
            RMQ[t++][0] = oldToNew[u];
        }
    }
    void build(int n) {
        this->numNodes = n;
        par[0] = MP(0, 0);
        M00(i, numNodes) depth[i] = 0;
        dfs(0, 0, 0);
        t = 0;
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            oldToNew[u] = t++;
            for(auto& v: adj[u]) if(par[u].F != v.F) q.push(v.F);
        }
        M00(i, numNodes) newToOld[oldToNew[i]] = i;
        t = 0;
        buildtarr(0);
        MOO(j, 1, LGSZ) M00(i, 2*numNodes-1) if(i+(1<<(j-1)) < 2*numNodes-1)
            RMQ[i][j] = min(RMQ[i][j-1], RMQ[i+(1<<(j-1))][j-1]);
    }
    int lca(int u, int v) {
        u = oldToNew[u], v = oldToNew[v];
        if(tin[u] > tin[v]) swap(u, v);
        int l = tin[u];
        int r = tin[v];
        int len = r-l+1;
        int hl = 31-__builtin_clz(len-1);
        return newToOld[min(RMQ[l][hl], RMQ[r-(1<<hl)+1][hl])];
    }
    ll dist(int u, int v) {
        return distfromroot[u]+distfromroot[v]-2*distfromroot[lca(u, v)];
    }
};

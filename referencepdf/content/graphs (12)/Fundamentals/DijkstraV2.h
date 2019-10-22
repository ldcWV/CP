/**
 * Description: Dijkstra's algorithm for shortest path
 * Time: O(V^2)
 * Source: lmao
 * Verification: lmao imagine verifying
 */

template<int SZ> struct dijkstra {
    vector<pair<int, ll>> adj[SZ];
    bool vis[SZ];
    ll d[SZ];
    
    void addEdge(int u, int v, ll l) {
        adj[u].PB(MP(v, l));
    }
    ll dist(int v) {
        return d[v];
    }
    void build(int u) {
        M00(i, SZ) vis[i] = 0;
        M00(i, SZ) d[i] = 1e17;
        d[u] = 0;
        while(1) {
            pair<ll, int> t = MP(1e17, -1);
            M00(i, SZ) if(!vis[i]) t = min(t, MP(d[i], i));
            if(t.S == -1) return;
            vis[t.S] = 1;
            
            for(auto& v: adj[t.S]) if(!vis[v.F]) {
                if(d[v.F] > d[t.S] + v.S) d[v.F] = d[t.S] + v.S;
            }
        }
    }
};

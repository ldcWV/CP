/**
 * Description: Dijkstra's algorithm for shortest path
 * Time: O(E\log V)
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
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        M00(i, SZ) d[i] = 1e17;
        d[u] = 0;
        pq.push(MP(0, u));
        while(!pq.empty()) {
            pair<ll, int> t = pq.top(); pq.pop();
            while(!pq.empty() && vis[t.S]) t = pq.top(), pq.pop();
            vis[t.S] = 1;
            
            for(auto& v: adj[t.S]) if(!vis[v.F]) {
                if(d[v.F] > d[t.S] + v.S) {
                    d[v.F] = d[t.S] + v.S;
                    pq.push(MP(d[v.F], v.F));
                }
            }
        }
    }
};

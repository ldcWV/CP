/**
 * Description: Dijkstra's algorithm for shortest path
 * Time: O(E\log V)
 * Source: lmao
 * Verification: lmao imagine verifying
 */

template<int SZ> struct dijkstra {
    const int inf = 1e8;
    vector<pi> adj[SZ];
    bool vis[SZ];
    int d[SZ];

    void addEdge(int u, int v, int l) {
        adj[u].pb(mp(v, l));
    }
    int dist(int v) {
        return d[v];
    }
    void build(int u) {
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        M00(i, SZ) d[i] = inf;
        d[u] = 0;
        pq.push(mp(0, u));
        while(!pq.empty()) {
            pi t = pq.top(); pq.pop();
            if(vis[t.s]) continue;
            vis[t.s] = 1;

            for(auto v: adj[t.s]) {
                if(d[v.f] > d[t.s] + v.s) {
                    d[v.f] = d[t.s] + v.s;
                    pq.push(mp(d[t.s]+v.s, v.f));
                }
            }
        }
    }
};

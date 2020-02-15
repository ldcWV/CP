/**
 * Description: can support tree path queries and updates
 * Time: $O(N\log N)$
 * Source: own
 * Verification: 
	* https://codeforces.com/contest/342/problem/E
	* Triway Cup 2019 G
 */

template<int SZ> struct centroidDecomp {
    vi neighbor[SZ];
    int subsize[SZ];
    bool vis[SZ];
    int p[SZ];
    int par[SZ];
    vi child[SZ];
    int numNodes;
    
    centroidDecomp(int num) {
        this->numNodes = num;
    }
    void addEdge(int u, int v) {
        neighbor[u].PB(v);
        neighbor[v].PB(u);
    }
    void build() {
        M00(i, numNodes) vis[i] = 0, par[i] = -1;
        solve(0);
        M00(i, numNodes) if(par[i] != -1) child[par[i]].PB(i);
    }
    void getSizes(int node) {
        subsize[node] = 1;
        for(int ch: neighbor[node]) if(!vis[ch] && ch != p[node]) {
            p[ch] = node;
            getSizes(ch);
            subsize[node] += subsize[ch];
        }
    }
    int getCentroid(int root) {
        p[root] = -1;
        getSizes(root);
        int cur = root;
        while(1) {
            pi hi = MP(subsize[root]-subsize[cur], cur);
            for(int v: neighbor[cur]) if(!vis[v] && v != p[cur]) hi = max(hi, MP(subsize[v], v));
            if(hi.F <= subsize[root]/2) return cur;
            cur = hi.S;
        }
    }
    int solve(int node) {
        node = getCentroid(node);
        vis[node] = 1;
        for(int ch: neighbor[node]) if(!vis[ch]) par[solve(ch)] = node;
        return node;
    }
};

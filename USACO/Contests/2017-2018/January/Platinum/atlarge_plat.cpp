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

const int MAX_N = 70007;
const int BITSZ = MAX_N; // change to MAX_N for 100% chance of working
int n;
vi adj[MAX_N];
int subsz[MAX_N];
int curT = 0;
int t[MAX_N];
int invt[MAX_N];
int deg[MAX_N];
int depth[MAX_N];
int distToLeaf[MAX_N];
int vis[MAX_N];

int dfs(int u, int d) {
    depth[u] = d;
    subsz[u] = 1;
    invt[curT] = u;
    t[u] = curT++;
    for(int v: adj[u]) if(subsz[v] == 0) {
        subsz[u] += dfs(v, d+1);
    }
    return subsz[u];
}

template<int sz> struct BIT {
    int b[sz+1];
    BIT() {
        M00(i, sz+1) b[i] = 0;
    }
    void add(int k, int val) {
        k++;
        for(; k <= sz; k+=(k&-k)) b[k] += val;
    }
    int psum(int ind) {
        int ans = 0;
        ind++;
        for(; ind>0; ind-=(ind&-ind)) ans += b[ind];
        return ans;
    }
    int sum(int l, int r) {
        return psum(r) - psum(l-1);
    }
};

const int blocksz = 250;

struct block {
    BIT<2*BITSZ>* bit;
    int lazy;
    block() {
        bit = new BIT<2*BITSZ>();
        lazy = 0;
    }
};

const int numblocks = (MAX_N + blocksz - 1)/blocksz;
block* blocks[numblocks];
int to[MAX_N];
int ans[MAX_N];

void rebuild(int i, int l, int r, int v) {
    block* b = blocks[i];
    MOO(j, l, r+1) {
        int indbit = to[invt[j]];
        //cout << indbit << "\n";
        b->bit->add(indbit + v, 2 - deg[invt[j]]);
        b->bit->add(indbit, deg[invt[j]] - 2);
        to[invt[j]] += v;
    }
}

void upd(int l, int r, int v) {
    int ind = l;
    if(l/blocksz == r/blocksz) {
        rebuild(l/blocksz, l, r, v);
    } else {
        rebuild(l/blocksz, l, blocksz*(l/blocksz + 1) - 1, v);
        ind = blocksz*(l/blocksz + 1);
        while(ind/blocksz != r/blocksz) {
            blocks[ind/blocksz]->lazy += v;
            ind += blocksz;
        }
        rebuild(r/blocksz, ind, r, v);
    }
}

int query() {
    int ans = 0;
    M00(i, numblocks) {
        //cout << MAX_N - blocks[i]->lazy << "\n";
        ans += blocks[i]->bit->sum(0, BITSZ - blocks[i]->lazy);
    }
    return ans;
}

void dfs2(int u) {
    if(adj[u].size() == 1) {
        ans[u] = 1;
    } else {
        // assert(query() > 0);
        ans[u] = query();
    }
    for(int v: adj[u]) if(ans[v] == -1) {
        // add 1 to all subtree differences & subtract 1 from all other nodes
        upd(t[v], t[v] + subsz[v]-1, 2);
        M00(i, numblocks) blocks[i]->lazy -= 1;
        dfs2(v);
        // do opposite
        upd(t[v], t[v] + subsz[v]-1, -2);
        M00(i, numblocks) blocks[i]->lazy += 1;
    }
}

int main() { FAST
    ofstream fout("atlarge.out");
    ifstream fin("atlarge.in");
    fin >> n;
    M00(i, n-1) {
        int a, b; fin >> a >> b;
        a--; b--;
        adj[a].PB(b);
        adj[b].PB(a);
    }
    dfs(0, 0);
    M00(i, n) deg[i] = (int)adj[i].size();
    queue<pi> bfsQueue;
    M00(i, n) {
        if((int)adj[i].size() == 1) {
            bfsQueue.push(MP(i, 0));
            vis[i] = 1;
        }
    }
    while(!bfsQueue.empty()) {
        pi t = bfsQueue.front();
        bfsQueue.pop();
        distToLeaf[t.F] = t.S;
        for(int v: adj[t.F]) if(!vis[v]) {
            vis[v] = 1;
            bfsQueue.push(MP(v, t.S+1));
        }
    }
    M00(i, n) to[i] = BITSZ + distToLeaf[i] - depth[i];
    M00(i, numblocks) {
        blocks[i] = new block();
    }
    M00(i, n) {
        blocks[t[i]/blocksz]->bit->add(to[i], 2 - deg[i]);
    }
    M00(i, n) ans[i] = -1;
    dfs2(0);
    M00(i, n) {
        fout << ans[i] << "\n";
    }
}

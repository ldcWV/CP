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
#define sz(v) (int)v.size()

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

const int MAX_Q = 100010;
int q;
pi queries[MAX_Q];
int n = 0;
int par[MAX_Q];
int ppar[MAX_Q][17];
int depth[MAX_Q];
vi ch[MAX_Q];
int comp[MAX_Q];
pi dia[MAX_Q];

void setComp(int u, int c) {
    comp[u] = c;
    for(int v: ch[u]) setComp(v, c);
}

void setDepth(int u, int d) {
    depth[u] = d;
    for(int v: ch[u]) setDepth(v, d+1);
}

int lca(int u, int v) {
    if(comp[u] != comp[v]) return -1;
    if(depth[u] != depth[v]) {
        if(depth[u] > depth[v]) swap(u, v);
        // move v up to u
        M00d(i, 17) if(ppar[v][i] != -1) {
            if(depth[ppar[v][i]] >= depth[u]) v = ppar[v][i];
        }
    }
    if(u == v) return u;
    M00d(i, 17) if(ppar[u][i] != -1) {
        if(ppar[u][i] != ppar[v][i]) {
            u = ppar[u][i];
            v = ppar[v][i];
        }
    }
    assert(u != v && par[u] == par[v]);
    return par[u];
}

int dis(int u, int v) {
    if(comp[u] != comp[v]) return -1;
    return depth[u] + depth[v] - 2*depth[lca(u, v)];
}

int main() { FAST
    freopen("newbarn.in","r",stdin);
    freopen("newbarn.out","w",stdout);
    cin >> q;
    M00(i, q) {
        char a; cin >> a;
        queries[i].F = (a=='Q');
        cin >> queries[i].S;
        if(queries[i].S != -1) queries[i].S--;
    }
    M00(i, q) {
        if(queries[i].F == 0) {
            par[n] = queries[i].S;
            if(queries[i].S != -1) ch[queries[i].S].PB(n);
            n++;
        }
    }
    int comps = 0;
    M00(i, n) {
        if(par[i] == -1) {
            setComp(i, comps++);
            setDepth(i, 0);
        }
    }
    M00(i, n) {
        ppar[i][0] = par[i];
        MOO(j, 1, 17) {
            if(ppar[i][j-1] == -1) ppar[i][j] = -1;
            else ppar[i][j] = ppar[ppar[i][j-1]][j-1];
        }
    }
    M00(i, comps) dia[i] = MP(-1, -1);
    int curNode = 0;
    M00(i, q) {
        if(queries[i].F == 0) { // build
            int component = comp[curNode];
            if(queries[i].S == -1) {
                dia[component] = MP(curNode, curNode);
            } else {
                if(dia[component].F == dia[component].S) dia[component].S = curNode;
                else {
                    if(dis(dia[component].F, dia[component].S) < dis(dia[component].F, curNode)) {
                        dia[component].S = curNode;
                    } else if(dis(dia[component].F, dia[component].S) < dis(dia[component].S, curNode)) {
                        dia[component].F = curNode;
                    }
                }
            }
            curNode++;
        } else { // query
            int node = queries[i].S;
            int component = comp[node];
            cout << max(dis(node, dia[component].F), dis(node, dia[component].S)) << "\n";
        }
    }
}

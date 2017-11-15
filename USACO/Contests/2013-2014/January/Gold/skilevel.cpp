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

struct eyg {
    pii v1;
    pii v2;
    ll length;
    eyg(pii a, pii b, ll l) {
        this->v1 = a;
        this->v2 = b;
        this->length = l;
    }
    bool operator <(const eyg& other) const {
        return length < other.length;
    }
};

struct lel {
    int sz;
    pii par;
    lel(int s, pii p) {
        this->sz = s;
        this->par = p;
    }
};

template<int w, int h> struct DSU {
    lel* e[w][h];
    DSU() {
        M00(i, w) M00(j, h) {
            e[i][j] = new lel(1, MP(i, j));
        }
    }
    pii get(pii x) {
        int i = x.F;
        int j = x.S;
        if(e[i][j]->par != MP(i, j)) {
            e[i][j]->par = get(e[i][j]->par);
        }
        return e[i][j]->par;
    }
    void unite(pii x, pii y) {
        x = get(x);
        y = get(y);
        if(x == y) return;
        lel* xp = e[x.F][x.S];
        lel* yp = e[y.F][y.S];
        if(xp->sz < yp->sz) swap(xp, yp), swap(x, y);
        xp->sz += yp->sz, yp->par = x;
    }
    bool connected(pii x, pii y) {
        x = get(x);
        y = get(y);
        return (x == y);
    }
    int s(pii x) { //size of component containing x
        x = get(x);
        return e[x.F][x.S]->sz;
    }
};

const int MAX_N = 505;
int n, m;
int t;
ll arr[MAX_N][MAX_N];
ll ans[MAX_N][MAX_N];
vector<pii> eygList[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
vector<eyg> el;

void dfs(pii x, ll c) {
    if(vis[x.F][x.S]) return;
    vis[x.F][x.S] = 1;
    ans[x.F][x.S] = c;
    for(pii y: eygList[x.F][x.S]) dfs(y, c);
}

int main() { FAST
    ofstream fout("skilevel.out");
    ifstream fin("skilevel.in");
    fin >> n >> m >> t;
    M00(i, n) M00(j, m) fin >> arr[i][j];
    M00(i, n) M00(j, m) {
        eyg e1 = eyg(MP(-1, -1), MP(-1, -1), -1);
        eyg e2 = eyg(MP(-1, -1), MP(-1, -1), -1);
        if(i+1 < n) e1 = eyg(MP(i, j), MP(i+1, j), abs(arr[i][j] - arr[i+1][j]));
        if(j+1 < m) e2 = eyg(MP(i, j), MP(i, j+1), abs(arr[i][j] - arr[i][j+1]));
        if(e1.length != -1) el.PB(e1);
        if(e2.length != -1) el.PB(e2);
    }
    sort(el.begin(), el.end());
    DSU<MAX_N, MAX_N> d;
    for(eyg& a: el) {
        if(d.connected(a.v1, a.v2)) continue;
        d.unite(a.v1, a.v2);
        eygList[a.v1.F][a.v1.S].PB(MP(a.v2.F, a.v2.S));
        eygList[a.v2.F][a.v2.S].PB(MP(a.v1.F, a.v1.S));
        if(d.s(a.v1) >= t) dfs(a.v1, a.length);
        if(d.s(a.v2) >= t) dfs(a.v2, a.length);
    }
    ll total = 0;
    M00(i, n) M00(j, m) {
        char c; fin >> c;
        if(c == '1') {
            total += ans[i][j];
        }
    }
    fout << total << "\n";
}

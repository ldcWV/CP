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
typedef pair<ll,ll> pi;

template<class T, int SZ> struct segtree {
    T tree[2*SZ+1], identity = 1e16;
    segtree() {
        M00(i, 2*SZ+1) tree[i] = identity;
    }
    T comb(T a, T b) {
        return min(a,b); // can change this
    }
    void upd(int pos, T val) {
        pos += SZ+1;
        tree[pos] = val!=1e16?min(tree[pos],val):1e16; // update leaf
        for(pos >>= 1; pos >= 1; pos >>= 1) {
            tree[pos] = comb(tree[2*pos], tree[2*pos+1]);
        }
    }
    T query(int l, int r) {
        l += SZ+1;
        r += SZ+1;
        T res = identity;
        while(l <= r) {
            if(l&1) res = comb(res, tree[l++]);
            if(!(r&1)) res = comb(res, tree[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

const int MAX_N = 100010;
int n, m;
segtree<ll, MAX_N*2> mm, mp, pm, pp;
pair<pi, ll> slingshots[MAX_N];
pi que[MAX_N];
vector<pair<pi,ll>> process;
map<pi, int> ans;
map<pair<pi,ll>, int> cy;

bool cmp(pair<pi,ll> p1, pair<pi,ll> p2) {
    if(p1.F.S == p2.F.S) return p1 < p2;
    return p1.F.S < p2.F.S;
}

int main() { FAST
    freopen("slingshot.in","r",stdin);
    freopen("slingshot.out","w",stdout);
    cin >> n >> m;
    M00(i, n) {
        cin >> slingshots[i].F.F >> slingshots[i].F.S >> slingshots[i].S;
        process.PB(slingshots[i]);
    }
    M00(i, m) {
        cin >> que[i].F >> que[i].S;
        process.PB(MP(que[i], -1));
    }
    sort(all(process), cmp);
    M00(i,sz(process)) {
        cy[process[i]] = i;
    }
    
    sort(all(process));
    for(pair<pi,ll> k: process) {
        int newy = cy[k];
        if(k.S != -1) {
            pm.upd(newy, k.F.F - k.F.S + k.S);
            pp.upd(newy, k.F.F + k.F.S + k.S);
        }
    }
    for(pair<pi,ll> k: process) {
        int newy = cy[k];
        if(k.S == -1) {
            ll res = abs(k.F.S-k.F.F);
            res = min(res, +k.F.F+k.F.S + mm.query(0, newy));
            res = min(res, +k.F.F-k.F.S + mp.query(newy, MAX_N*2-1));
            res = min(res, -k.F.F+k.F.S + pm.query(0, newy));
            res = min(res, -k.F.F-k.F.S + pp.query(newy, MAX_N*2-1));
            ans[k.F] = res;
        } else {
            mm.upd(newy, -k.F.F - k.F.S + k.S);
            mp.upd(newy, -k.F.F + k.F.S + k.S);
            pm.upd(newy, 1e16);
            pp.upd(newy, 1e16);
        }
    }
    M00(i, m) cout << ans[que[i]] << "\n";
}

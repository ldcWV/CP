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

template<class T, int SZ> struct maxtree {
    T tree[2*SZ+1], identity = 0;
    maxtree() {
        M00(i, 2*SZ+1) tree[i] = identity;
    }
    T comb(T a, T b) {
        return max(a,b); // can change this
    }
    void upd(int pos, T val) {
        pos += SZ+1;
        tree[pos] = val; // update leaf
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

template<class T, int SZ> struct sumtree {
    T tree[2*SZ+1], identity = 0;
    sumtree() {
        M00(i, 2*SZ+1) tree[i] = identity;
    }
    T comb(T a, T b) {
        return a+b; // can change this
    }
    void upd(int pos, T val) {
        pos += SZ+1;
        tree[pos] = val; // update leaf
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
int n;
ld k;
int arr[MAX_N];
int lis[MAX_N];
ld cnt[MAX_N];
maxtree<int,MAX_N> s1;
vi q[MAX_N];
sumtree<ld,MAX_N> s2;

int main() { FAST
    freopen("itout.in","r",stdin);
    freopen("itout.out","w",stdout);
    cin >> n >> k;
    M00(i, n) cin >> arr[i];
    M00d(i, n) {
        lis[i] = 1 + s1.query(arr[i], n);
        s1.upd(arr[i], lis[i]);
    }
    M00(i, n) q[lis[i]].PB(i);
    for(int i: q[1]) {
        cnt[i] = 1;
    }
    MOO(val, 2, n) {
        int prev = val-1;
        int ptr = sz(q[prev])-1;
        M00d(i, sz(q[val])) {
            while(ptr >= 0 && q[prev][ptr] > q[val][i]) {
                s2.upd(arr[q[prev][ptr]], cnt[q[prev][ptr]]);
                ptr--;
            }
            cnt[q[val][i]] = s2.query(arr[q[val][i]], n);
        }
        for(int i: q[prev]) s2.upd(arr[i], 0);
    }
    
    int mx = 0;
    M00(i, n) mx = max(mx, lis[i]);
    int last = -1;
    ld curcnt = 0;
    set<int> bad;
    MOOd(i, 1, mx+1) {
        vector<pi> possnext; // set of possible next indices (arr[index], index)
        for(int j: q[i]) {
            if(last == -1) possnext.PB(MP(arr[j],j));
            else {
                if(j > last && arr[j] > arr[last]) possnext.PB(MP(arr[j],j));
            }
        }
        sort(all(possnext));
        reverse(all(possnext));
        for(pi asdf: possnext) {
            int p = asdf.S;
            if(curcnt + cnt[p] < k-.1) curcnt += cnt[p];
            else {
                last = p;
                bad.insert(arr[last]);
                break;
            }
        }
    }
    assert(sz(bad) == mx);
    set<int> res;
    M00(i, n) if(!bad.count(arr[i])) res.insert(arr[i]);
    cout << sz(res) << "\n";
    for(int i: res) cout << i << "\n";
}

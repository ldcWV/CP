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

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a)+(b))%(b))

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 100000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

pair<pi, int> patches[MAX_N];
map<int, int> cx;
map<int, int> cy;

int n, k;
pair<pi, pi> sp[MAX_N];
pair<pi, pi> ep[MAX_N];

template<int SZ> struct lazymaxtree {
    int mx[2*SZ], lazy[2*SZ]; // set SZ to a power of 2
    
    lazymaxtree() {
        F0R(i, 2*SZ) mx[i] = 0, lazy[i] = 0;
    }
    
    void push(int ind, int L, int R) {
        mx[ind] += lazy[ind];
        if (L != R) lazy[2*ind] += lazy[ind], lazy[2*ind+1] += lazy[ind];
        lazy[ind] = 0;
    }
    
    void pull(int ind) {
        mx[ind] = max(mx[2*ind],mx[2*ind+1]);
    }
    
    void build() {
        for (int i = SZ-1; i > 0; --i) pull(i);
    }

    int query(int lo, int hi, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (lo > R || L > hi) return -1000000000;
        if (lo <= L && R <= hi) return mx[ind];
        
        int M = (L+R)/2;
        return max(query(lo,hi,2*ind,L,M),query(lo,hi,2*ind+1,M+1,R));
    }
    
    void upd(int lo, int hi, int inc, int ind = 1, int L = 0, int R = SZ-1) {
        push(ind,L,R);
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy[ind] = inc;
            push(ind,L,R);
            return;
        }
        
        int M = (L+R)/2;
        upd(lo,hi,inc,2*ind,L,M); upd(lo,hi,inc,2*ind+1,M+1,R);
        pull(ind);
    }
};

int main() {
    ofstream fout("lazy.out");
    ifstream fin("lazy.in");
    fin >> n >> k;
    F0R(i, n) {
        int x, y;
        fin >> patches[i].S >> x >> y;
        patches[i].F.F = x+y;
        patches[i].F.S = y-x;
    }
    F0R(i, n) {
        sp[i].F.F = patches[i].F.F - k; cx[sp[i].F.F] = 0;
        sp[i].S.F = patches[i].F.S - k; cy[sp[i].S.F] = 0;
        sp[i].S.S = patches[i].F.S + k; cy[sp[i].S.S] = 0;
        
        ep[i].F.F = patches[i].F.F + k; cx[ep[i].F.F] = 0;
        ep[i].S.F = patches[i].F.S - k; cy[ep[i].S.F] = 0;
        ep[i].S.S = patches[i].F.S + k; cy[ep[i].S.S] = 0;
        
        sp[i].F.S = patches[i].S;
        ep[i].F.S = -patches[i].S;
    }
    int k1 = 0, k2 = 0;
    for(auto& v : cx) v.S = k1++;
    for(auto& v : cy) v.S = k2++;
    F0R(i, n) {
        sp[i].F.F = cx[sp[i].F.F];
        sp[i].S.F = cy[sp[i].S.F];
        sp[i].S.S = cy[sp[i].S.S];
        
        ep[i].F.F = cx[ep[i].F.F];
        ep[i].S.F = cy[ep[i].S.F];
        ep[i].S.S = cy[ep[i].S.S];
    }
    sort(begin(sp), begin(sp) + n);
    sort(begin(ep), begin(ep) + n);
    
    lazymaxtree<1<<18> tree;
    int indS = 0;
    int indE = 0;
    int hi = 0;
    while(indS < n) {
        if(indE == n || sp[indS].F.F <= ep[indE].F.F) {
            int xval = sp[indS].F.F;
            while(indS < n && sp[indS].F.F == xval)
                tree.upd(sp[indS].S.F, sp[indS].S.S, sp[indS].F.S), indS++;
            hi = max(hi, tree.query(0, 2*n-1));
        }
        else {
            int xval = ep[indE].F.F;
            while(indE < n && ep[indE].F.F == xval)
                tree.upd(ep[indE].S.F, ep[indE].S.S, ep[indE].F.S), indE++;
        }
    }
    fout << hi << "\n";
}

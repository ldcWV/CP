#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

template<int SZ> struct mstree {
    Tree<int> val[SZ+1]; // for offline queries use vector instead
    
    void upd(int x, int y) { // x-coordinate between 1 and SZ inclusive
        x++;
        for (;x <= SZ; x += (x&-x)) val[x].insert(y);
    }
    
    int query(int x, int y) {
        x++;
        int t = 0;
        for (;x > 0; x -= (x&-x)) t += val[x].order_of_key(y+1);
        return t;
    }
    
    int query(int lox, int hix, int loy, int hiy) { // query number of elements within a rectangle
        return query(hix,hiy)-query(lox-1,hiy)-query(hix,loy-1)+query(lox-1,loy-1);
    }
};

template<int sz> struct BIT {
    int b[sz+1];
    BIT() {
        M00(i, sz) b[i] = 0;
    }
    void add(int k, int val) {
        k++;
        for(; k <= sz; k+=(k&-k)) b[k] += val;
    }
    int psum(int ind) {
        int ans = 0;
        ind++;
        for(; ind>0; ind-=(ind&-ind)) ans+=b[ind];
        return ans;
    }
    int sum(int l, int r) {
        return psum(r) - psum(l-1);
    }
};

const int MAX_N = 100000;
int n, k;
int l1[MAX_N];
pi l2[MAX_N];
pi arr[MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("friendcross.out");
    ifstream fin("friendcross.in");
    fin >> n >> k;
    M00(i, n) {
        fin >> l1[i];
        l1[i]--;
    }
    M00(i, n) {
        fin >> l2[i].F;
        l2[i].F--;
        l2[i].S = i;
    }
    sort(begin(l2), begin(l2) + n);
    M00(i, n) {
        arr[i].F = l1[i];
        arr[i].S = l2[l1[i]].S;
    }
    mstree<MAX_N> t;
    ll friendly = 0;
    M00d(i, n) {
        friendly += t.query(0, arr[i].S, max(0, arr[i].F-k), min(n-1, arr[i].F+k));
        t.upd(arr[i].S, arr[i].F);
    }
    
    ll total = 0;
    BIT<MAX_N> t2;
    M00d(i, n) {
        total += t2.sum(0, arr[i].S);
        t2.add(arr[i].S, 1);
    }
    fout << total - friendly << "\n";
}

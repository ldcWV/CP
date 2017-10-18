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

int n, k;
pair<pi, pi> sp[MAX_N];
pair<pi, pi> ep[MAX_N];

struct node {
    int val;
    int lazy;
    int l, r;
    node* left;
    node* right;
    node(int l, int r) {
        this -> val = 0;
        this -> lazy = 0;
        this -> l = l;
        this -> r = r;
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

template<int SZ> struct lazymaxtree {
    node* root;
    lazymaxtree() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node(0, ub-1);
    }
    void propagate(node* n) {
        if(n->l != n->r) {
            int mid = ((n->l) + (n->r))/2;
            if(n->left == nullptr) {
                n->left = new node(n->l, mid);
            }
            if(n->right == nullptr) {
                n->right = new node(mid+1, n->r);
            }
        }
        if(n->lazy != 0) {
            n->val += n->lazy;
            if(n->l != n->r) {
                n->left->lazy += n->lazy;
                n->right->lazy += n->lazy;
            }
            n->lazy = 0;
        }
    }
    void updN(node* n, int i1, int i2, int val) {
        propagate(n);
        if(i2 < n->l || i1 > n->r) return;
        if(n->l == n->r) {
            n->val += val;
            return;
        }
        if(i1 <= n->l && i2 >= n->r) {
            n->val += val;
            n->left->lazy += val;
            n->right->lazy += val;
            return;
        }
        
        updN(n->left, i1, i2, val);
        updN(n->right, i1, i2, val);
        n->val = max(n->left->val, n->right->val);
    }
    void upd(int i1, int i2, int val) {
        updN(root, i1, i2, val);
    }
    int queryN(node* n, int i1, int i2) {
        propagate(n);
        if(i2 < n->l || i1 > n->r) return -(1<<30)+1-(1<<30);
        if(n->l == n->r) {
            return n->val;
        }
        if(i1 <= n->l && i2 >= n->r) {
            return n->val;
        }
        
        return max(queryN(n->left, i1, i2), queryN(n->right, i1, i2));
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
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
        sp[i].F.F = 3000000+patches[i].F.F - k;
        sp[i].S.F = 3000000+patches[i].F.S - k;
        sp[i].S.S = 3000000+patches[i].F.S + k;
        
        ep[i].F.F = 3000000+patches[i].F.F + k;
        ep[i].S.F = 3000000+patches[i].F.S - k;
        ep[i].S.S = 3000000+patches[i].F.S + k;
        
        sp[i].F.S = patches[i].S;
        ep[i].F.S = -patches[i].S;
    }
    sort(begin(sp), begin(sp) + n);
    sort(begin(ep), begin(ep) + n);
    
    lazymaxtree<5000000> tree;
    int indS = 0;
    int indE = 0;
    int hi = 0;
    while(indS < n) {
        if(indE == n || sp[indS].F.F <= ep[indE].F.F) {
            int xval = sp[indS].F.F;
            while(indS < n && sp[indS].F.F == xval)
                tree.upd(sp[indS].S.F, sp[indS].S.S, sp[indS].F.S), indS++;
            hi = max(hi, tree.query(0, 5000000-1));
        }
        else {
            int xval = ep[indE].F.F;
            while(indE < n && ep[indE].F.F == xval)
                tree.upd(ep[indE].S.F, ep[indE].S.S, ep[indE].F.S), indE++;
        }
    }
    fout << hi << "\n";
}

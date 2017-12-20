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

const ll MOD = 1000000007;
int n;
ll minFlav;
const int MAX_N = 100000;
ll flav[MAX_N];
ll spic[MAX_N];

struct node {
    ll val;
    int l, r;
    node* left;
    node* right;
    node(int l, int r) {
        this -> val = 0;
        this -> l = l;
        this -> r = r;
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

template<int SZ> struct maxtree{
    node* root;
    maxtree() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node(0, ub-1);
        root -> val = (-(1<<30)+1)-(1<<30);
    }
    void updN(node* n, int pos, ll val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            n->val = val;
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) n->right = new node(mid+1, n->r), n->right->val = (-(1<<30)+1)-(1<<30);
            updN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) n->left = new node(n->l, mid), n->left->val = (-(1<<30)+1)-(1<<30);
            updN(n->left, pos, val);
        }
        
        ll s = (-(1<<30)+1)-(1<<30);
        if(n->left != nullptr) s = max(s, n->left->val);
        if(n->right != nullptr) s = max(s, n->right->val);
        
        n->val = s;
    }
    void upd(int pos, ll val) {
        updN(root, pos, val);
    }
    ll queryN(node* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return (-(1<<30)+1)-(1<<30);
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        ll s = (-(1<<30)+1)-(1<<30);
        if(n->left != nullptr) s = max(s, queryN(n->left, i1, i2));
        if(n->right != nullptr) s = max(s, queryN(n->right, i1, i2));
        
        return s;
    }
    ll query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

ll psum[MAX_N];

ll sum(int l, int r) {
    if(l == 0) return psum[r];
    return psum[r] - psum[l-1];
}

int main() { FAST
    ofstream fout("hayfeast.out");
    ifstream fin("hayfeast.in");
    fin >> n >> minFlav;
    M00(i, n) fin >> flav[i] >> spic[i];
    maxtree<MAX_N> ms;
    M00(i, n) ms.upd(i, spic[i]);
    psum[0] = flav[0];
    MOO(i, 1, n) psum[i] = psum[i-1] + flav[i];
    int r = 0;
    ll ans = 100000000000000000;
    M00(l, n) {
        r = max(r, l);
        while(r < n && sum(l, r) < minFlav) r++;
        if(r == n) break;
        ans = min(ans, ms.query(l, r));
    }
    fout << ans << "\n";
}

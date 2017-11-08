/*
 ID: ldorian1
 LANG: C++11
 TASK: hopscotch
 */

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

#define MOD 1000000007

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int m(int k) {
    if(k < 0) return (k+MOD) % MOD;
    return k % MOD;
}

struct node {
    int val;
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

template<int SZ> struct sumtree{
    node* root;
    sumtree() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node(0, ub-1);
    }
    void updN(node* n, int pos, int val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            n->val += val;
            n->val = m(n->val);
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) n->right = new node(mid+1, n->r);
            updN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) n->left = new node(n->l, mid);
            updN(n->left, pos, val);
        }
        
        int s = 0;
        if(n->right != nullptr) s += n->right->val;
        if(n->left != nullptr) s += n->left->val;
        
        n->val = s;
        n->val = m(n->val);
    }
    void upd(int pos, int val) {
        updN(root, pos, val);
    }
    int queryN(node* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return 0;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        int s = 0;
        if(n->left != nullptr) s += queryN(n->left, i1, i2);
        if(n->right != nullptr) s += queryN(n->right, i1, i2);
        
        return m(s);
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

int r, c, k;
int arr[750][750];
sumtree<750> t[750*750];
int dp[750][750];
int pref[750][750];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("hopscotch.out");
    ifstream fin("hopscotch.in");
    fin >> r >> c >> k;
    F0R(i, r) F0R(j, c) fin >> arr[i][j], arr[i][j]--;
    dp[r-1][c-1] = 1;
    t[arr[r-1][c-1]].upd(r-1, 1);
    F0R(i, r-1) dp[i][c-1] = 0, pref[i][c-1] = 1;
    F0R(i, c-1) dp[r-1][i] = 0, pref[r-1][i] = 1;
    pref[r-1][c-1] = 1;
    F0Rd(j, c-1) {
        F0Rd(i, r-1) {
            int color = arr[i][j];
            dp[i][j] = pref[i+1][j+1] - t[color].query(i+1, r-1);
            dp[i][j] = m(dp[i][j]);
            if(dp[i][j] < 0) dp[i][j] += MOD;
            pref[i][j] = dp[i][j] + pref[i+1][j];
            pref[i][j] = m(pref[i][j]);
            pref[i][j] += pref[i][j+1];
            pref[i][j] = m(pref[i][j]);
            pref[i][j] -= pref[i+1][j+1];
            pref[i][j] = m(pref[i][j]);
        }
        F0R(i, r) {
            t[arr[i][j]].upd(i, dp[i][j]);
        }
    }
    cout << dp[0][0] << "\n";
}

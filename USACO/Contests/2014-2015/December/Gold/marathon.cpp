/*
 ID: ldorian1
 LANG: C++11
 TASK: marathon
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

#define MAX_N 100000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, q;
pi points[MAX_N];

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
            n->val = val;
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(n->left == nullptr) n->left = new node(n->l, mid);
        if(n->right == nullptr) n->right = new node(mid+1, n->r);
        
        updN(n->left, pos, val);
        updN(n->right, pos, val);
        n->val = n->left->val + n->right->val;
    }
    void upd(int pos, int val) {
        updN(root, pos, val);
    }
    int queryN(node* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return 0;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        int mid = (n->l + n->r)/2;
        if(n->left == nullptr) n->left = new node(n->l, mid);
        if(n->right == nullptr) n->right = new node(mid+1, n->r);
        
        return queryN(n->left, i1, i2) + queryN(n->right, i1, i2);
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
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
    void updN(node* n, int pos, int val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            n->val = val;
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(n->left == nullptr) {
            n->left = new node(n->l, mid);
            n->left->val = (-(1<<30)+1)-(1<<30);
        }
        if(n->right == nullptr) {
            n->right = new node(mid+1, n->r);
            n->right->val = (-(1<<30)+1)-(1<<30);
        }
        
        updN(n->left, pos, val);
        updN(n->right, pos, val);
        n->val = max(n->left->val, n->right->val);
    }
    void upd(int pos, int val) {
        updN(root, pos, val);
    }
    int queryN(node* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return (-(1<<30)+1)-(1<<30);
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        int mid = (n->l + n->r)/2;
        if(n->left == nullptr) {
            n->left = new node(n->l, mid);
            n->left->val = (-(1<<30)+1)-(1<<30);
        }
        if(n->right == nullptr) {
            n->right = new node(mid+1, n->r);
            n->right->val = (-(1<<30)+1)-(1<<30);
        }
        
        return max(queryN(n->left, i1, i2), queryN(n->right, i1, i2));
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

int dist(pi p1, pi p2) {
    return (abs(p1.F - p2.F) + abs(p1.S - p2.S));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("marathon.out");
    ifstream fin("marathon.in");
    fin >> n >> q;
    F0R(i, n) fin >> points[i].F >> points[i].S;
    
    sumtree<MAX_N+5> t1;
    maxtree<MAX_N+5> t2;
    
    F0R(i, n-1) {
        t1.upd(i, dist(points[i], points[i+1]));
        if(i != 0) t2.upd(i, dist(points[i-1], points[i]) + dist(points[i], points[i+1]) - dist(points[i-1], points[i+1]));
    }
    
    F0R(i, q) {
        char c; fin >> c;
        if(c == 'U') {
            int ind; fin >> ind; ind--;
            fin >> points[ind].F >> points[ind].S;
            
            if(ind > 0) t1.upd(ind-1, dist(points[ind-1], points[ind]));
            if(ind < n-1) t1.upd(ind, dist(points[ind], points[ind+1]));
            
            if(ind > 1) t2.upd(ind-1, dist(points[ind-2], points[ind-1]) + dist(points[ind-1], points[ind]) - dist(points[ind-2], points[ind]));
            if(ind > 0 && ind < n-1) t2.upd(ind, dist(points[ind-1], points[ind]) + dist(points[ind], points[ind+1]) - dist(points[ind-1], points[ind+1]));
            if(ind < n-2) t2.upd(ind+1, dist(points[ind], points[ind+1]) + dist(points[ind+1], points[ind+2]) - dist(points[ind], points[ind+2]));
        }
        else {
            int i1, i2; fin >> i1 >> i2; i1--; i2--;
            int total = 0;
            if(i1 != i2) total = t1.query(i1, i2-1);
            int reduced = 0;
            if(i1+1 < i2) reduced = t2.query(i1+1, i2-1);
            fout << total-reduced << "\n";
        }
    }
}

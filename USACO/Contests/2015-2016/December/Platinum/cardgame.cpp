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

struct cardInterval {
    int paired;
    int coverable;
    int cancover;
    cardInterval(){}
    cardInterval(int a, int b, int c) {
        this->paired = a;
        this->coverable = b;
        this->cancover = c;
    }
};

template<class T> struct node {
    T val;
    int l, r;
    node* left;
    node* right;
    node(int l, int r) {
        this -> l = l;
        this -> r = r;
        this -> val = cardInterval(0, 0, 0);
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

template<class T, int SZ> struct hicard{
    node<T>* root;
    T identity = cardInterval(0, 0, 0); //[comb(identity, other) = comb(other, identity) = other] or this won't work
    T comb(T l, T r) {
        int p = min(l.coverable, r.cancover);
        return cardInterval(l.paired + r.paired + p, l.coverable + r.coverable - p, l.cancover + r.cancover - p);
    }
    void updLeaf(node<T>* l, T val) {
        l->val = val;
    }
    
    hicard() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node<T>(0, ub-1);
        root->val = identity;
    }
    void updN(node<T>* n, int pos, T val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            updLeaf(n, val);
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) {
                n->right = new node<T>(mid+1, n->r);
                n->right->val = identity;
            }
            updN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) {
                n->left = new node<T>(n->l, mid);
                n->left->val = identity;
            }
            updN(n->left, pos, val);
        }
        
        T lv = (n->left == nullptr) ? identity : n->left->val;
        T rv = (n->right == nullptr) ? identity : n->right->val;
        n->val = comb(lv, rv);
    }
    void upd(int pos, T val) {
        updN(root, pos, val);
    }
    T queryN(node<T>* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return identity;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        T a = identity;
        if(n->left != nullptr) a = comb(a, queryN(n->left, i1, i2));
        if(n->right != nullptr) a = comb(a, queryN(n->right, i1, i2));
        
        return a;
    }
    T query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

template<class T, int SZ> struct locard{
    node<T>* root;
    T identity = cardInterval(0, 0, 0); //[comb(identity, other) = comb(other, identity) = other] or this won't work
    T comb(T l, T r) {
        int p = min(l.cancover, r.coverable);
        return cardInterval(l.paired + r.paired + p, l.coverable + r.coverable - p, l.cancover + r.cancover - p);
    }
    void updLeaf(node<T>* l, T val) {
        l->val = val;
    }
    
    locard() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node<T>(0, ub-1);
        root->val = identity;
    }
    void updN(node<T>* n, int pos, T val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            updLeaf(n, val);
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) {
                n->right = new node<T>(mid+1, n->r);
                n->right->val = identity;
            }
            updN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) {
                n->left = new node<T>(n->l, mid);
                n->left->val = identity;
            }
            updN(n->left, pos, val);
        }
        
        T lv = (n->left == nullptr) ? identity : n->left->val;
        T rv = (n->right == nullptr) ? identity : n->right->val;
        n->val = comb(lv, rv);
    }
    void upd(int pos, T val) {
        updN(root, pos, val);
    }
    T queryN(node<T>* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return identity;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        T a = identity;
        if(n->left != nullptr) a = comb(a, queryN(n->left, i1, i2));
        if(n->right != nullptr) a = comb(a, queryN(n->right, i1, i2));
        
        return a;
    }
    T query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

const int MAX_N = 50505;
bool u[MAX_N*2+1];
vi bess;
vi other;
int n;

int main() { FAST
    ofstream fout("cardgame.out");
    ifstream fin("cardgame.in");
    fin >> n;
    M00(i, n) {
        int k; fin >> k;
        other.PB(k);
        u[other[i]] = 1;
    }
    MOO(i, 1, 2*n + 1) {
        if(!u[i]) bess.PB(i);
    }
    sort(bess.begin(), bess.end());
    hicard<cardInterval, MAX_N*2+1> hi;
    locard<cardInterval, MAX_N*2+1> lo;
    //initially everything is low card
    M00(i, n) {
        lo.upd(other[i], cardInterval(0, 1, 0));
        lo.upd(bess[i], cardInterval(0, 0, 1));
    }
    int ans = 0;
    M00(i, n+1) { //first i games is high card
        ans = max(ans, hi.query(1, 2*n+1).paired + lo.query(1, 2*n+1).paired);
        if(i == n) break;
        hi.upd(other[i], cardInterval(0, 1, 0));
        hi.upd(bess[n-i-1], cardInterval(0, 0, 1));
        lo.upd(other[i], cardInterval(0, 0, 0));
        lo.upd(bess[n-i-1], cardInterval(0, 0, 0));
    }
    fout << ans << "\n";
}

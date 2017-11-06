/*
 ID: ldorian1
 LANG: C++11
 TASK:
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

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;

const int MAX_N = 101010;
int n, t;
pll in[MAX_N];
pair<pair<pll, pll>, pii> paths[MAX_N];
map<ll, int> cx;
map<ll, int> cy;
vector<tuple<int, bool, int, int, int, int>> q; //y coord, isQuery, x1, x2, update amount, and time

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

struct st{
    node* root;
    st(int SZ) {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node(0, ub-1);
    }
    void addN(node* n, int pos, int val) {
        if(pos < n->l || pos > n->r) return;
        n->val += val;
        if(n->l == n->r) {
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) n->right = new node(mid+1, n->r);
            addN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) n->left = new node(n->l, mid);
            addN(n->left, pos, val);
        }
    }
    void add(int pos, int val) {
        addN(root, pos, val);
    }
    int queryN(node* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return 0;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        int ans = 0;
        if(n->left != nullptr) ans += queryN(n->left, i1, i2);
        if(n->right != nullptr) ans += queryN(n->right, i1, i2);
        
        return ans;
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

template<int w, int l> struct segbit {
    st* b[w+1];
    segbit() {
        M00(i, w+1) b[i] = new st(l);
    }
    void add(int x, int y, int val) {
        x++;
        for(; x <= w; x+=(x&-x)) b[x]->add(y, val);
    }
    int psum(int x, int y1, int y2) {
        int ret = 0;
        x++;
        for(; x>0; x-=(x&-x)) ret+=b[x]->query(y1, y2);
        return ret;
    }
    int sum(int x1, int y1, int x2, int y2) {
        return psum(x2, y1, y2) - psum(x1-1, y1, y2);
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

ll solve() {
    M00(i, n-1) {
        paths[i].F.F = in[i];
        paths[i].F.S = in[i+1];
        if(paths[i].F.F.F == paths[i].F.S.F) { //vert
            paths[i].S.F=1;
        }
    }
    M00(i, n-1) {
        if(abs(paths[i].F.F.F-paths[i].F.S.F) + abs(paths[i].F.F.S-paths[i].F.S.S) > 1) {
            if(paths[i].S.F) { //vertical
                if(paths[i].F.F.S > paths[i].F.S.S) swap(paths[i].F.F, paths[i].F.S);
                paths[i].F.F.S++;
                paths[i].F.S.S--;
            }
            else { //horizontal
                if(paths[i].F.F.F > paths[i].F.S.F) swap(paths[i].F.F, paths[i].F.S);
                paths[i].F.F.F++;
                paths[i].F.S.F--;
            }
        }
        else {
            paths[i].F.F.F = -1;
        }
    }
    M00(i, n-1) {
        if(paths[i].F.F.F != -1) {
            cx[paths[i].F.F.F] = 0;
            cx[paths[i].F.S.F] = 0;
            cy[paths[i].F.F.S] = 0;
            cy[paths[i].F.S.S] = 0;
        }
        else {
            paths[i].F.F.F = -1;
        }
    }
    int temp = 0;
    for(auto& v: cx) v.S = temp++;
    temp = 0;
    for(auto& v: cy) v.S = temp++;
    M00(i, n-1) {
        if(paths[i].F.F.F != -1) {
            paths[i].F.F.F = cx[paths[i].F.F.F];
            paths[i].F.S.F = cx[paths[i].F.S.F];
            paths[i].F.F.S = cy[paths[i].F.F.S];
            paths[i].F.S.S = cy[paths[i].F.S.S];
            paths[i].S.S = i+1;
        }
    }
    
    //go from lowest y to highest y
    M00(i, n-1) if(paths[i].F.F.F != -1) {
        if(!paths[i].S.F) { //horizontal, then it is a query
            tuple<int, bool, int, int, int, int> que = make_tuple(paths[i].F.F.S, 1, paths[i].F.F.F, paths[i].F.S.F, -1, paths[i].S.S);
            q.PB(que);
        }
        else { //vertical - update
            tuple<int, bool, int, int, int, int> u1 = make_tuple(paths[i].F.F.S, 0, paths[i].F.F.F, -1, 1, paths[i].S.S);
            tuple<int, bool, int, int, int, int> u2 = make_tuple(paths[i].F.S.S+1, 0, paths[i].F.F.F, -1, -1, paths[i].S.S);
            q.PB(u1);
            q.PB(u2);
        }
    }
    sort(q.begin(), q.end());
    
    BIT<3*MAX_N/2> b;
    segbit<3*MAX_N/2, MAX_N> s;
    ll total = 0;
    ll comp = 0;
    M00(i, q.size()) {
        bool isQuery = get<1>(q.at(i));
        if(!isQuery) {
            b.add(get<2>(q.at(i)), get<4>(q.at(i)));
            s.add(get<2>(q.at(i)), get<5>(q.at(i)), get<4>(q.at(i)));
        }
        else {
            total += b.sum(get<2>(q.at(i)), get<3>(q.at(i)));
            comp += s.sum(get<2>(q.at(i)), max(0, get<5>(q.at(i))-t), get<3>(q.at(i)),  min(n, get<5>(q.at(i))+t));
        }
    }
    return total-comp;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("mowing.out");
    ifstream fin("mowing.in");
    fin >> n >> t;
    M00(i, n) fin >> in[i].F >> in[i].S;
    fout << solve() << "\n";
}

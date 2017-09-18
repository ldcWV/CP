/*
 ID: ldorian1
 LANG: C++11
 TASK: haybales
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
#define MAX_N 200000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int treeSize=1;
int n, q;
ll arr[MAX_N];
ll s[524288];
ll z[524288];
ll m[524288];

void propagate(int k, int x, int y) {
    if(z[k]!=0) {
        s[k]+=z[k]*(y-x+1);
        m[k]+=z[k];
        if(!(x==y)) { //if it is not a leaf
            z[2*k]+=z[k];
            z[2*k+1]+=z[k];
        }
        z[k]=0;
    }
}

void update(int u, int a, int b, int k, int x, int y) {
    propagate(k, x, y);
    if(b<x || a>y) return;
    if(x>=a && y<=b) {
        s[k]+=(ll)(y-x+1)*(ll)(u);
        m[k]+=u;
        if(x!=y) {
            z[k*2]+=u;
            z[k*2+1]+=u;
        }
        return;
    }
    int d = (x+y)/2;
    update(u, a, b, 2*k, x, d);
    update(u, a, b, 2*k+1, d+1, y);
    s[k]=s[k*2]+s[k*2+1];
    m[k]=min(m[k*2], m[k*2+1]);
}

ll sum(int a, int b, int k, int x, int y) {
    propagate(k, x ,y);
    if(b<x || a>y) return 0;
    if(x>=a && y<=b) return s[k];
    int d = (x+y)/2;
    return sum(a,b,2*k,x,d)+sum(a,b,2*k+1,d+1,y);
}

ll mi(int a, int b, int k, int x, int y) {
    propagate(k, x, y);
    if(b<x || a>y) return 200000000000;
    if(x>=a && y<=b) return m[k];
    int d = (x+y)/2;
    return min(mi(a,b,2*k,x,d),mi(a,b,2*k+1,d+1,y));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("haybales.out");
    ifstream fin("haybales.in");
    fin >> n >> q;
    F0R(i, n) fin >> arr[i];
    while(treeSize <= 2*n) treeSize*=2;
    FORd(i, 1, treeSize) {
        if(i>=treeSize/2+n) {
            s[i]=0;
            m[i]=200000000000;
        }
        else if(i>=treeSize/2) {
            s[i]=arr[i-treeSize/2];
            m[i]=arr[i-treeSize/2];
        }
        else {
            s[i]=s[2*i]+s[2*i+1];
            m[i]=min(m[2*i], m[2*i+1]);
        }
    }
    F0R(i, q) {
        char a; fin >> a;
        if(a=='P') {
            int a, b, c; fin >> a >> b >> c;
            a--; b--;
            update(c, a, b, 1, 0, treeSize/2-1);
        }
        else if(a=='S') {
            int a, b; fin >> a >> b;
            a--; b--;
            fout << sum(a, b, 1, 0, treeSize/2-1) << "\n";
        }
        else {
            int a, b; fin >> a >> b;
            a--; b--;
            fout << mi(a, b, 1, 0, treeSize/2-1) << "\n";
        }
    }
}

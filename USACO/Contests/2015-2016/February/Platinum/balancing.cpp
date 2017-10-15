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

#define MAX_N 100005

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
pi p[MAX_N];

template<int SZ> struct BIT {
    int bit[SZ+1];
    
    BIT() {
        F0R(i, SZ+1) bit[i]=0;
    }
    
    void upd(int k, int v) {
        k++;
        for(; k<=SZ; k+=(k&-k)) bit[k]+=v;
    }
    
    int psum(int k) {
        k++;
        int s = 0;
        for(; k>0; k-=(k&-k)) s+=bit[k];
        return s;
    }
    
    int sum(int k1, int k2) {
        return psum(k2) - psum(k1-1);
    }
};

BIT<MAX_N+1> b1;
BIT<MAX_N+1> b2;

int cost(int k) {
    return max(b1.sum(0, k), max(b1.sum(k+1, n-1), max(b2.sum(0, k), b2.sum(k+1, n-1))));
}

int s1(int k) {
    return max(b1.sum(0, k), b2.sum(0,k));
}

int s2(int k) {
    return max(b1.sum(k+1, n-1), b2.sum(k+1, n-1));
}

bool w(int k) {
    if(k == n-1) return 1;
    return (s1(k) >= s2(k));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("balancing.out");
    ifstream fin("balancing.in");
    fin >> n;
    map<int, int> compressX;
    map<int, int> compressY;
    F0R(i, n) {
        fin >> p[i].F >> p[i].S;
        compressX[p[i].F] = 0;
        compressY[p[i].S] = 0;
    }
    int temp = 0;
    for(auto& c : compressX) c.S = temp++;
    temp = 0;
    for(auto& c : compressY) c.S = temp++;
    int last = 0;
    F0R(i, n) {
        p[i].F = compressX[p[i].F];
        p[i].S = compressY[p[i].S];
        last = max(last, p[i].S);
    }
    sort(begin(p), begin(p) + n);
    
    F0R(i, n) b2.upd(p[i].S, 1);
    
    int ind = -1;
    for(int jump = last/2; jump>0; jump/=2) {
        while(ind+jump <= last && !w(ind+jump)) ind+=jump;
    }
    ind++;
    int lo = cost(ind);
    if(ind != 0) lo = min(lo, cost(ind-1));
    
    F0R(i, n-1) {
        b1.upd(p[i].S, 1);
        b2.upd(p[i].S, -1);
        while(i<n-1 && p[i].F == p[i+1].F) {
            i++;
            b1.upd(p[i].S, 1);
            b2.upd(p[i].S, -1);
        }
        int curr = -1;
        for(int jump = last/2; jump>0; jump/=2) {
            while(curr+jump <= last && !w(curr+jump)) curr+=jump;
        }
        curr++;
        lo = min(lo, cost(curr));
        if(curr != 0) lo = min(lo, cost(curr-1));
    }
    fout << lo << "\n";
}

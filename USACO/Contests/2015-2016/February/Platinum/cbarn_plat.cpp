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
typedef pair<int,int> pi;
typedef pair<ll, int> pll;

const int MAX_N = 1000;
int n, k;
int shift;
ll arr[MAX_N];
ll cost[MAX_N][MAX_N]; //cost[l][r] = 0*arr[l]+1*arr[l+1]+...+(r-l)*arr[r]
ll dp[MAX_N][8]; //dp[i][j] is <min cost using first i rooms with j doors, position of jth door>

ll c(int l, int r) {
    return cost[(l+shift)%n][(r+shift)%n];
}

int mod(int k) {
    while(k < 0) k+=n;
    return k%n;
}

void solve(int l, int r, int d, int lb, int ub) { //we know position of dth door is in [lb, ub]
    int mid = (l+r)/2;
    //want to calculate dp[mid][d]
    if(d >= mid) {
        dp[mid][d] = 0;
        if(l != r) solve(l, mid, d, lb, mid);
        if(l != r) solve(mid+1, r, d, mid, ub);
        return;
    }
    ll lo = 1e15;
    int place = lb;
    MOO(i, lb, ub+1) {
        if(i > 0) {
            if(dp[i-1][d-1] + c(i, mid) < lo) {
                lo = dp[i-1][d-1] + c(i, mid);
                place = i;
            }
        }
        else {
            if(c(i, r) < lo) {
                lo = c(i, mid);
                place = i;
            }
        }
    }
    dp[mid][d] = lo;
    if(l != r) solve(l, mid, d, lb, place);
    if(l != r) solve(mid+1, r, d, place, ub);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("cbarn.out");
    ifstream fin("cbarn.in");
    fin >> n >> k;
    M00(i, n) fin >> arr[i];
    M00(i, n) M00(j, n) {
        int j1 = mod(i+j);
        if(i == j1) cost[i][j1] = 0;
        else if(j1 > i) {
            cost[i][j1] = cost[i][j1-1]+(ll)(j1-i)*arr[j1];
        }
        else {
            cost[i][j1] = cost[i][mod(j1-1)]+(ll)(n-i+j1)*arr[j1];
        }
    }
    
    ll lo = 1e15;
    for( ; shift<n; shift++) {
        M00(i, n) {
            dp[i][1] = c(0, i);
        }
        MOO(j, 2, k+1) solve(0, n-1, j, 0, n-1);
        lo = min(lo, dp[n-1][k]);
    }
    fout << lo << "\n";
}

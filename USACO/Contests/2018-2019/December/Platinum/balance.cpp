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
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <sstream>

using namespace std;

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << '\n', 0;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<ll,ll> pi;

const int MAX_N = 100005;
int n;
ll f[MAX_N];

bool ccw(pi a, pi b, pi c) {
    return (b.F-a.F)*(c.S-a.S) - (b.S-a.S)*(c.F-a.F) > 0;
}

int main() { FAST
    freopen("balance.in","r",stdin);
    freopen("balance.out","w",stdout);
    cin >> n;
    MOO(i, 1, n+1) cin >> f[i];
    n += 2;
    vector<pi> hull;
    M00(i, n) {
        while(sz(hull) >= 2 && ccw(hull[sz(hull)-2], hull[sz(hull)-1], MP(i, f[i]))) {
            hull.pop_back();
        }
        hull.PB(MP(i,f[i]));
    }
    int ind = 0;
    MOO(i, 1, n-1) {
        if(hull[ind+1].F <= i) ind++;
        ll Y1 = hull[ind].S;
        ll Y2 = hull[ind+1].S;
        ll X = i;
        ll X1 = hull[ind].F;
        ll X2 = hull[ind+1].F;
        cout << (100000LL*((X-X1)*Y2+(X2-X)*Y1)/(X2-X1)) << "\n";
    }
}

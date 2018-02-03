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
const int MAX_N = 100000;
int n;
pi points[MAX_N];
ll lo[MAX_N];
ll hi[MAX_N];

ll psum[MAX_N];
ll sqsum[MAX_N];

ll rsum(int l, int r) {
    if(l == 0) return psum[r];
    return psum[r] - psum[l-1];
}

ll rsqsum(int l, int r) {
    if(l == 0) return sqsum[r];
    return sqsum[r] - sqsum[l-1];
}

int main() { FAST
    ofstream fout("sprinklers.out");
    ifstream fin("sprinklers.in");
    fin >> n;
    M00(i, n) fin >> points[i].F >> points[i].S;
    sort(points, points + n);
    lo[0] = points[0].S;
    MOO(i, 1, n-1) {
        lo[i] = min(lo[i-1], (ll)points[i].S);
    }
    hi[n-2] = points[n-1].S;
    M00d(i, n-2) {
        hi[i] = max(hi[i+1], (ll)points[i+1].S);
    }
    psum[0] = hi[0];
    sqsum[0] = SQ(hi[0]);
    MOO(i, 1, n-1) {
        psum[i] = psum[i-1] + hi[i];
        sqsum[i] = sqsum[i-1] + SQ(hi[i]);
    }
    ll ans = 0;
    int x2 = 0;
    M00(i, n-1) {
        x2 = max(x2, i);
        ll y = lo[i];
        ll res = 0;
        while(x2 < n-1) {
            if(hi[x2] <= y) break;
            x2++;
        }
        x2--;
        if(x2 < i) continue;
        res += rsqsum(i, x2);
        res -= (2*y-1) * rsum(i, x2);
        res += y*y * (ll)(x2 - i + 1);
        res -= y * (ll)(x2 - i + 1);
        assert(res%2 == 0);
        res /= 2;
        res %= MOD;
        ans += res;
        ans %= MOD;
    }
    fout << ans << "\n";
}

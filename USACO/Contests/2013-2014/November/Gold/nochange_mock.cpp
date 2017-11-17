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
#include <assert.h>

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

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int MAX_K = 16;
const int MAX_N = 100000;
int n, k;
ll values[MAX_K];
ll pref[MAX_N];
pair<ll, int> dp[1 << MAX_K]; //cost, index

int main() { FAST
    ofstream fout("nochange.out");
    ifstream fin("nochange.in");
    fin >> k >> n;
    M00(i, k) fin >> values[i];
    fin >> pref[0];
    M00(i, n-1) {
        ll val; fin >> val;
        pref[i+1] = pref[i]+val;
    }
    ll total = 0;
    M00(i, k) total += values[i];
    ll hi = -1;
    MOO(i, 1, 1<<k) {
        ll cost = dp[i-(1<<__builtin_ctz(i))].F + values[__builtin_ctz(i)];
        dp[i].F = cost;
        M00(j, k) if(i & (1 << j)) {
            int before = i - (1 << j);
            pair<ll, int> d = dp[before];
            ll alr = (d.S > 0) ? pref[d.S-1] : 0;
            dp[i].S = max(dp[i].S,(int)(upper_bound(pref, pref+n, alr+values[j]) - begin(pref)));
        }
        if(dp[i].S == n) {
            hi = max(hi, total - cost);
        }
    }
    fout << hi << "\n";
}

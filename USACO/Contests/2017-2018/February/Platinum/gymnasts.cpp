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
#define sz(v) (int)v.size()

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << '\n', 0;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;

const ll MOD = 1000000007;
ll n;
ll sieve[100010];
map<ll, int> prifac;
vector<ll> p;
vector<int> a;

ll getpow(ll base, ll exp) {
    if(exp == 0) return 1;
    ll res = getpow(base, exp/2);
    if(exp%2 == 0) return (res*res) % MOD;
    return (((res*res)%MOD)*base)%MOD;
}

void ins(ll pri) {
    if(prifac.count(pri)) prifac[pri]++;
    else prifac[pri] = 1;
}

ll curphi = 1;
ll curd = 1;
ll res = 0;

void solve(int ind) {
    ll initphi = curphi;
    ll initd = curd;
    if(ind == sz(p)-1) {
        for(ll i = 0; i <= a[ind]; i++) {
            if(i != 0) {
                curd *= p[ind];
            }
            if(i == 1) {
                curphi *= p[ind]-1;
            } else if(i >= 2) {
                curphi *= p[ind];
            }
            res += (getpow(2, n/curd)*curphi) % MOD; res %= MOD;
        }
    } else {
        for(ll i = 0; i <= a[ind]; i++) {
            if(i != 0) {
                curd *= p[ind];
            }
            if(i == 1) {
                curphi *= p[ind]-1;
            } else if(i >= 2) {
                curphi *= p[ind];
            }
            solve(ind+1);
        }
    }
    curphi = initphi;
    curd = initd;
}

int main() { FAST
    freopen("gymnasts.in","r",stdin);
    freopen("gymnasts.out","w",stdout);
    cin >> n;
    MOO(i, 2, 100010) if(sieve[i] == 0) {
        for(int j = i; j < 100010; j += i) {
            sieve[j] = i;
        }
    }
    ll temp = n;
    // prime factorize
    for(ll x = 2; x*x <= temp; x++) {
        while(temp%x == 0) {
            temp /= x;
            ins(x);
        }
    }
    if(temp > 1) ins(temp);
    for(auto k: prifac) {
        p.PB(k.F);
        a.PB(k.S);
    }
    solve(0);
    res -= getpow(2, n); res %= MOD; res += MOD; res %= MOD;
    res -= n; res %= MOD; res += MOD; res %= MOD;
    res += 2; res %= MOD;
    finish(res);
}

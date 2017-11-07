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

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

const ll INF = 1000000000000000;
const int MAX_N = 20;
int n;
ll h;
pair<ll, ll> dp[1 << MAX_N]; //height, strength
ll height[MAX_N];
ll weight[MAX_N];
ll strength[MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("guard.out");
    ifstream fin("guard.in");
    fin >> n >> h;
    M00(i, n) fin >> height[i] >> weight[i] >> strength[i];
    dp[0] = MP(0, INF);
    ll ans = -1;
    MOO(i, 1, 1 << n) {
        ll hi = -INF;
        M00(j, n) if(i & (1 << j)) {
            dp[i].F = dp[i-(1<<j)].F + height[j];
            hi = max(hi, min(strength[j], dp[i-(1<<j)].S-weight[j]));
        }
        dp[i].S = hi;
        if(dp[i].F >= h) ans = max(ans, dp[i].S);
    }
    if(ans != -1) fout << ans << "\n";
    else fout << "Mark is too tall\n";
}

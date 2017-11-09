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

int n;
ll t;
const int MAX_N = 100000;
pair<ll, ll> seg[MAX_N];
ll tail[MAX_N];
const ll inf = 1000000002000000000;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("cowjog.out");
    ifstream fin("cowjog.in");
    fin >> n >> t;
    M00(i, n) {
        fin >> seg[i].F;
        ll b; fin >> b;
        seg[i].S = seg[i].F + b*t;
    }
    sort(begin(seg), begin(seg) + n);
    reverse(begin(seg), begin(seg)+n);
    
    ll v[MAX_N]; M00(i, MAX_N) v[i] = inf;
    int ans = 1;
    MOO(i, 1, n+1) {
        int j = (int)(upper_bound(begin(v), begin(v)+n, seg[i-1].S) - begin(v));
        v[j] = seg[i-1].S;
        ans = max(ans, j+1);
    }
    fout << ans << "\n";
}

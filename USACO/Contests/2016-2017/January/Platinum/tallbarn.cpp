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

#define MAX_N 100000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef long double ld;

int n;
ll k;
ll arr[MAX_N];

ld cost(ll a, ll b) {
    return ((ld)(a))/((ld)(b) * (ld)(b+1));
}

ll cowsNeeded(ld c) { //for each floor, add cows until the profit is less than cost
    ll ans = 0;
    M00(i, n) {
        ld d = ((ld)(arr[i]))/c;
        int k = floor(sqrt(1.0+4*d)-1)/2.0;
        ans += k;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("tallbarn.out");
    ifstream fin("tallbarn.in");
    fin >> n >> k;
    k-=n;
    M00(i, n) fin >> arr[i];
    ld hi = 1e18;
    ld lo = 0;
    ld mid = 0;
    M00(i, 300) {
        mid = (lo+hi)/2;
        if(cowsNeeded(mid) >= k) lo = mid;
        else hi = mid;
    }
    ld ans = 0.0;
    ll tot = 0;
    M00(i, n) {
        ld d = ((ld)(arr[i]))/lo;
        int v = floor((sqrt(1.0+4*d)-1)/2.0);
        tot += v;
        ans += ((ld)(arr[i]))/((ld)(v+1));
    }
    fout << llround(ans+(tot-k)*lo) << "\n";
}

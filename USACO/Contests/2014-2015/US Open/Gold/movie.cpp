/*
 ID: ldorian1
 LANG: C++11
 TASK: movie
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

#define MAX_N 20

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
ll len;
ll d[MAX_N];
vi st[MAX_N];
ll dp[1 << MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("movie.out");
    ifstream fin("movie.in");
    
    fin >> n >> len;
    F0R(i, n) {
        int num;
        fin >> d[i] >> num;
        F0R(j, num) {
            int k; fin >> k;
            st[i].PB(k);
        }
    }
    
    dp[0] = 0;
    F0R(i, n) {
        dp[1 << i] = (st[i].at(0) == 0) ? d[i] : 0;
    }
    int mi = 21;
    F0R(i, 1 << n) if(__builtin_popcount(i) > 1 && __builtin_popcount(i) < mi) {
        ll best = 0;
        F0R(j, n) if(i & (1 << j)) {
            ll k = dp[i - (1<<j)];
            int ind = (int)(upper_bound(st[j].begin(), st[j].end(), k) - begin(st[j]));
            if(ind == 0) {
                best = max(best, k);
                continue;
            }
            ind--; //ind is last index in st[j] that fits
            best = max(best, max(st[j].at(ind) + d[j], k));
        }
        dp[i] = best;
        if(dp[i] >= len) mi = __builtin_popcount(i);
    }
    int ans =(mi != 21) ? mi : -1;
    fout << ans << "\n";
}

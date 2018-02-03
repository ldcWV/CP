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
const int MAX_N = 100005;
const int MAX_K = 105;
set<pi> segs;
vector<pi> segz;
int n, k;
pair<ll, int> dp[2][MAX_K][2]; // total intersection length, last covered

int main() { FAST
    ofstream fout("lifeguards.out");
    ifstream fin("lifeguards.in");
    fin >> n >> k;
    M00(i, n) {
        int l, r;
        fin >> l >> r;
        segs.insert(MP(l, r));
    }
    
    //get rid of completely covered segments
    int maxr = -1;
    vector<pi> toremove;
    for(auto i: segs) {
        if(i.S <= maxr) toremove.PB(i);
        else {
            maxr = i.S;
        }
    }
    M00(i, (int)toremove.size()) segs.erase(toremove[i]);
    k -= n - (int)segs.size();
    n = (int)segs.size();
    if(k <= 0) {
        ll t = 0;
        maxr = -1;
        for(auto i: segs) {
            if(i.F <= maxr) {
                t += i.S - maxr;
            } else {
                t += i.S - i.F;
            }
            maxr = i.S;
        }
        fout << t << "\n";
    } else {
        segz.PB(MP(0, -1)); // 1 index
        for(auto i: segs) segz.PB(i);
        M00(i, 2) M00(j, k+1) M00(b, 2) dp[i][j][b] = MP(0, -2);
        dp[1][0][0] = MP(segz[1].S - segz[1].F, segz[1].S);
        dp[1][1][1] = MP(0, -1);
        //cout << "1" << " " << "0" << " 0: " << dp[1][0][0].F << ", " << dp[1][0][0].S << "\n";
        //cout << "1" << " " << "1" << " 1: " << dp[1][1][1].F << ", " << dp[1][1][1].S << "\n";
        MOO(i, 2, n+1) {
            M00(j, k+1) {
                // if we keep the ith segment
                if(dp[(i-1)%2][j][0].S != -2) // if we keep the i-1 th segment
                    dp[i%2][j][0] = MP(dp[(i-1)%2][j][0].F + min(segz[i].S - dp[(i-1)%2][j][0].S, segz[i].S - segz[i].F), segz[i].S);
                if(dp[(i-1)%2][j][1].S != -2) // if we delete the i-1 th segment
                    dp[i%2][j][0] = max(MP(dp[(i-1)%2][j][1].F + min(segz[i].S - dp[(i-1)%2][j][1].S, segz[i].S - segz[i].F), segz[i].S), dp[i%2][j][0]);
                // if we delete the ith segment
                if(j != 0 && dp[(i-1)%2][j-1][0].S != -2) { // if we keep the i-1 th segment
                    dp[i%2][j][1] = dp[(i-1)%2][j-1][0];
                }
                if(j != 0 && dp[(i-1)%2][j-1][1].S != -2) { // if we delete the i-1 th segment
                    dp[i%2][j][1] = max(dp[(i-1)%2][j-1][1], dp[i%2][j][1]);
                }
                //cout << i << " " << j << " 0: " << dp[i][j][0].F << ", " << dp[i][j][0].S << "\n";
                //cout << i << " " << j << " 1: " << dp[i][j][1].F << ", " << dp[i][j][1].S << "\n";
            }
        }
        cout << max(dp[n%2][k][0], dp[n%2][k][1]).F << "\n";
    }
}

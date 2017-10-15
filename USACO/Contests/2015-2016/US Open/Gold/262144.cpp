/*
 ID: ldorian1
 LANG: C++11
 TASK: 262144
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

#define MAX_N 262144

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
pair<bool, int> dp[MAX_N][60]; //is possible? if so, index
int arr[MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("262144.out");
    ifstream fin("262144.in");
    fin >> n;
    F0R(i, n) {
        fin >> arr[i];
        arr[i]--;
    }
    int hi = 0;
    F0R(i, n) {
        dp[i][arr[i]].F = 1;
        hi = max(hi, arr[i]);
        dp[i][arr[i]].S = i;
    }
    FOR(i, 1, 60) {
        F0R(j, n) {
            int s2 = dp[j][i-1].S+1;
            if(dp[j][i-1].F && s2 < n && dp[s2][i-1].F) {
                dp[j][i].F = 1;
                dp[j][i].S = dp[dp[j][i-1].S+1][i-1].S;
                hi = max(hi, i);
            }
        }
    }
    fout << hi+1 << "\n";
}

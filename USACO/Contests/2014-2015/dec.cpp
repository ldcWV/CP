/*
 ID: ldorian1
 LANG: C++11
 TASK: dec
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

#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a)+(b))%(b))

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 20
#define MAX_B 20

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

struct triple {
    int F, S, T;
    triple() {}
    triple(int a, int b, int c) : F(a), S(b), T(c) {}
};

int n, b;
int arr[MAX_N][MAX_N];
int req[MAX_N];
int dp[1<<MAX_N];
triple bonus[MAX_B];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("dec.out");
    ifstream fin("dec.in");
    fin >> n >> b;
    F0R(i, b) {
        int ind; fin >> ind; ind--;
        int r; fin >> r;
        int val; fin >> val;
        bonus[i] = triple(ind, r, val);
    }
    F0R(i, n) F0R(j, n) fin >> arr[i][j];

    dp[0]=0;
    FOR(i, 1, 1 << n) {
        int numElements = __builtin_popcount(i)-1;
        int bestInd = __builtin_ctz(i);
        FOR(j, 0, n) if(i & (1<<j)) {
            int remaining = i-(1<<j);
            bestInd = (dp[remaining]+arr[j][numElements] > dp[i-(1<<bestInd)]+arr[bestInd][numElements]) ? j : bestInd;
        }
        int bon = 0;
        int val = dp[i-(1<<bestInd)]+arr[bestInd][numElements];
        F0R(j, b) {
            if(bonus[j].F==numElements && val>=bonus[j].S) {
                bon+=bonus[j].T;
            }
        }
        dp[i] = val+bon;
    }
    fout << dp[(1<<n)-1] << "\n";
}

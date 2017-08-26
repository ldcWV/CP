/*
 ID: ldorian1
 LANG: C++11
 TASK: test2
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
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)


#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 10

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int costs[MAX_N][MAX_N];
int n, d;
int dp[1<<MAX_N][MAX_N];

void printBits(int a) { //for debugging
    F0Rd(i, 32) {
        if(a&(1<<i)) cout << "1";
        else cout << "0";
    }
    cout << endl;
}

int solve(int a, int b) {
    if(dp[a][b]!=-1) return dp[a][b];
    if(b==0 && __builtin_popcount(a)>1) return 1000000; //if impossible
    int currMin=solve(a,b-1);
    F0R(i, n) {
        if(a&(1<<i)) {
            currMin=min(currMin, solve(a-(1<<i), b-1)+costs[i][b]);
        }
    }
    dp[a][b]=currMin;
    return currMin;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("test2.out");
    ifstream fin("test2.in");
    fin >> n >> d;
    F0R(i, n) F0R(j, d) fin >> costs[i][j];
    F0R(i, 1<<n) F0R(j, d) dp[i][j]=-1;
    F0R(i, d) dp[0][i]=0;
    F0R(i, n) dp[1<<i][0]=costs[i][0];
    cout << solve((1<<n)-1, d-1) << endl;
}

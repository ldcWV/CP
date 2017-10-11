/*
 ID: ldorian1
 LANG: C++11
 TASK: skicourse
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

#define MAX_N 100

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, m;
int arr[MAX_N][MAX_N];
int dp1[MAX_N][MAX_N];
int dp2[MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("skicourse.out");
    ifstream fin("skicourse.in");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) {
        char s; fin >> s;
        if(s=='R') arr[i][j]=1;
        else arr[i][j]=2;
    }
    int ans = 100;
    while(true) {
        int sz = 0;
        F0R(i, n) {
            dp1[i][0] = (arr[i][0]==0 || arr[i][0]==1);
            dp2[i][0] = (arr[i][0]==0 || arr[i][0]==2);
        }
        F0R(i, m) {
            dp1[0][i] = (arr[0][i]==0 || arr[0][i]==1);
            dp2[0][i] = (arr[0][i]==0 || arr[0][i]==2);
        }
        FOR(i, 1, n) FOR(j, 1, m) {
            if(arr[i][j]==1) {
                dp1[i][j] = 1+min(dp1[i][j-1], min(dp1[i-1][j], dp1[i-1][j-1]));
                dp2[i][j] = 0;
            }
            else if(arr[i][j]==2) {
                dp1[i][j] = 0;
                dp2[i][j] = 1+min(dp2[i][j-1], min(dp2[i-1][j], dp2[i-1][j-1]));
            }
            else {
                dp1[i][j] = 1+min(dp1[i][j-1], min(dp1[i-1][j], dp1[i-1][j-1]));
                dp2[i][j] = 1+min(dp2[i][j-1], min(dp2[i-1][j], dp2[i-1][j-1]));
            }
        }
        F0R(i, n) F0R(j, m) {
            if(!(dp1[i][j] == dp2[i][j])) {
                sz = max(sz, max(dp1[i][j], dp2[i][j]));
            }
        }
        bool done = true;
        F0R(i, n) F0R(j, m) if(arr[i][j] != 0) done = false;
        if(done) break;
        ans = min(ans, sz);
        F0R(i, n) F0R(j, m) if(!(dp1[i][j] == dp2[i][j])){
            if((dp1[i][j] == sz) || (dp2[i][j] == sz)) {
                FOR(a, i-sz+1, i+1) {
                    FOR(b, j-sz+1, j+1) {
                        arr[a][b] = 0;
                    }
                }
                goto out;
            }
        }
        out: ;
    }
    fout << ans << "\n";
}

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

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int MAX_N = 100;
int arr[MAX_N][MAX_N];
int dp1[MAX_N][MAX_N]; //max size without 1
int dp2[MAX_N][MAX_N]; //max size without 2
int n, m;

int main() { FAST
    ofstream fout("skicourse.out");
    ifstream fin("skicourse.in");
    int lo = 500;
    fin >> n >> m;
    M00(i, n) M00(j, m) {
        char c; fin >> c;
        arr[i][j] = (c=='R') ? 1:2;
    }
    M00(i, n*m) {
        M00(i, n) {
            dp1[i][m-1] = (arr[i][m-1] == 2 || arr[i][m-1] == 0) ? 1 : 0;
            dp2[i][m-1] = (arr[i][m-1] == 1 || arr[i][m-1] == 0) ? 1 : 0;
        }
        M00(i, m) {
            dp1[n-1][i] = (arr[n-1][i] == 2 || arr[n-1][i] == 0) ? 1 : 0;
            dp2[n-1][i] = (arr[n-1][i] == 1 || arr[n-1][i] == 0) ? 1 : 0;
        }
        M00d(i, n-1) M00d(j, m-1) {
            if(arr[i][j] == 1) {
                dp1[i][j] = 0;
            } else {
                dp1[i][j] = 1 + min(min(dp1[i+1][j], dp1[i][j+1]), dp1[i+1][j+1]);
            }
        }
        M00d(i, n-1) M00d(j, m-1) {
            if(arr[i][j] == 2) {
                dp2[i][j] = 0;
            } else {
                dp2[i][j] = 1 + min(min(dp2[i+1][j], dp2[i][j+1]), dp2[i+1][j+1]);
            }
        }
        int hi = 0;
        int bi = 0;
        int bj = 0;
        M00(i, n) M00(j, m) if(dp1[i][j] != dp2[i][j]) {
            int b = max(dp1[i][j], dp2[i][j]);
            if(b > hi) {
                hi = max(hi, b);
                bi = i;
                bj = j;
            }
        }
        MOO(i, bi, bi+hi) MOO(j, bj, bj+hi) arr[i][j] = 0;
        lo = min(lo, hi);
        bool out = 1;
        M00(i, n) M00(j, m) if(arr[i][j] != 0) out = 0;
        if(out) break;
    }
    fout << lo << "\n";
}

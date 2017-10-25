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

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

const int MAX_N = 51;
int n;
int arr[MAX_N];
int dp[MAX_N][MAX_N][MAX_N][MAX_N];

int solve(int left, int right, int a, int b) {
    if(dp[left][right][a][b] != -1) return dp[left][right][a][b];
    if(left == right) return (arr[left] >= a && arr[left] <= b);
    if(right < left) return 0;
    if(b < a) return 0;
    
    int ans = 0;
    int al = arr[left];
    int ar = arr[right];
    
    //if keep
    ans = max(ans, solve(left+1, right, a, b));
    if(a <= al && al <= b) ans = max(ans, 1+solve(left+1, right, al, b));
    ans = max(ans, solve(left, right-1, a, b));
    if(a <= ar && ar <= b) ans = max(ans, 1+solve(left, right-1, a, ar));
    if(al >= a && ar <= b && al <= ar) ans = max(ans, 2+solve(left+1, right-1, al, ar));
    
    //if swap
    swap(al, ar);
    ans = max(ans, solve(left+1, right-1, a, b));
    if(a <= al && al <= b) ans = max(ans, 1+solve(left+1, right-1, al, b));
    if(a <= ar && ar <= b) ans = max(ans, 1+solve(left+1, right-1, a, ar));
    if(al >= a && ar <= b && al <= ar) ans = max(ans, 2+solve(left+1, right-1, al, ar));
    
    dp[left][right][a][b] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("subrev.out");
    ifstream fin("subrev.in");
    fin >> n;
    M00(i, n) fin >> arr[i];
    M00(a, n) M00(b, n) M00(c, MAX_N) M00(d, MAX_N) dp[a][b][c][d] = -1;
    fout << solve(0, n-1, 0, 51) << "\n";
}

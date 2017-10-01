/*
 ID: ldorian1
 LANG: C++11
 TASK: nocross
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

#define MAX_N 100000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
int top[MAX_N];
int bot[MAX_N];
vi neighbor[MAX_N]; //neighbor[i] stores all the neighbors of top[i]
int dp[MAX_N][9]; //dp[i][j] is max pairs using cows 0..i and i is connected to its jth neighbor
int tree[(1<<18)+1];

void update(int ind, int val) {
    ind += 1<<17;
    tree[ind] = max(tree[ind], val);
    ind/=2;
    for(; ind>=1; ind/=2) {
        tree[ind] = max(tree[2*ind], tree[2*ind+1]);
    }
}

int q(int r) { //max in [0,r]
    r += 1<<17;
    int ans = 0;
    int l = 1<<17;
    while(l <= r) {
        if(l%2 == 1) ans = max(ans, tree[l++]);
        if(r%2 == 0) ans = max(ans, tree[r--]);
        l /= 2; r /= 2;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("nocross.out");
    ifstream fin("nocross.in");
    fin >> n;
    F0R(i, n)  {
        fin >> top[i];
        top[i]--;
    }
    F0R(i, n) {
        int v;
        fin >> v;
        bot[v-1]=i;
    }
    F0R(i, n) {
        int k = top[i];
        FOR(j, max(0, k-4), min(n, k+5)) neighbor[i].PB(bot[j]);
        sort(neighbor[i].begin(), neighbor[i].end());
    }
    
    F0R(i, neighbor[0].size()) dp[0][i] = 1;
    F0R(i, neighbor[0].size()) update(neighbor[0].at(i), dp[0][i]);
    int hi = 1;
    FOR(i, 1, n) {
        F0R(j, neighbor[i].size()) {
            dp[i][j] = q(neighbor[i].at(j)-1)+1;
            hi = max(hi, dp[i][j]);
        }
        F0R(j, neighbor[i].size()) {
            update(neighbor[i].at(j), dp[i][j]);
        }
    }
    fout << hi << "\n";
}

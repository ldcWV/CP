/*
 ID: ldorian1
 LANG: C++11
 TASK: promote
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
#include <cstring>

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
pair<ll, int> goodness[MAX_N];
int p[MAX_N];
vi children[MAX_N];
bool vis[MAX_N];
int arr[MAX_N];
int pos = 0;
int sz[MAX_N];
int bit[MAX_N+1];
int ans[MAX_N];

void dfs(int k) {
    if(vis[k]) return;
    arr[k]=pos;
    pos++;
    vis[k]=true;
    F0R(i, children[k].size()) dfs(children[k].at(i));
}

int dfs2(int k) {
    if(sz[k]!=0) return sz[k];
    int total = 0;
    F0R(i, children[k].size()) {
        total+=dfs2(children[k].at(i));
    }
    sz[k]=total+1;
    return total+1;
}

void update(int k) { //adds 1 to kth element in bit
    k++;
    for( ;k <= n; k += (k&-k)) bit[k]++;
}

int psum(int k) {
    k++;
    int s = 0;
    for( ;k>0; k-=(k&-k)) s+=bit[k];
    return s;
}

int sum(int l, int r) {
    return psum(r)-psum(l-1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("promote.out");
    ifstream fin("promote.in");
    fin >> n;
    F0R(i, n) fin >> goodness[i].F;
    F0R(i, n) goodness[i].S=i;
    FOR(i, 1, n) {
        fin >> p[i];
        p[i]--;
        children[p[i]].PB(i);
    }
    p[0]=-1;
    sort(begin(goodness), begin(goodness)+n);
    reverse(begin(goodness), begin(goodness)+n);
    dfs(0);
    dfs2(0);
    F0R(i, n) {
        int node = goodness[i].S;
        int k = arr[node];
        ans[node]=sum(k, k+sz[node]-1);
        update(k);
    }
    F0R(i, n) fout << ans[i] << "\n";
}

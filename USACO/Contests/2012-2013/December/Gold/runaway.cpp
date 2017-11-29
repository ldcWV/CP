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
#define PMOD(a, b) (((a) > 0) ? ((a)%(b)) : ((((a)+(b)*((-(a)/(b))+1))%(b))))
#define UMOD(a, b) (a) = (((a) > 0) ? ((a)%(b)) : ((((a)+(b)*((-(a)/(b))+1))%(b))))

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

const int MAX_N = 200000;
const int LG_N = 19;

int n;
ll l;
pair<int, ll> par[MAX_N];
vector<pair<int, ll>> children[MAX_N];
int ancestor[MAX_N+1][LG_N];
ll distTo[MAX_N];
int num[MAX_N+1];
int ans[MAX_N];

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

void dfs(int u, ll distSoFar) { //compute distance from root to u
    distTo[u] = distSoFar;
    for(auto& v: children[u]) dfs(v.F, distSoFar + v.S);
}

ll dist(int u, int v) { //u is an ancestor of v
    return distTo[v] - distTo[u];
}

int dfs2(int u) {
    if(children[u].size() == 0) {
        ans[u] = 1;
        return 1;
    }
    int res = num[u];
    for(auto& v: children[u]) res += dfs2(v.F);
    ans[u] = res;
    return res;
}

int main() { FAST
    ofstream fout("runaway.out");
    ifstream fin("runaway.in");
    fin >> n >> l;
    M00(i, n-1) {
        fin >> par[i+1].F >> par[i+1].S;
        par[i+1].F--;
        children[par[i+1].F].PB(MP(i+1, par[i+1].S));
    }
    dfs(0, 0);
    M00(i, n) ancestor[i][0] = par[i].F;
    MOO(j, 1, LG_N) {
        M00(i, n) ancestor[i][j] = ancestor[ancestor[i][j-1]][j-1];
    }
    M00(i, 19) ancestor[0][i] = n;
    ancestor[n][0] = n;
    
    num[0] = 1;
    MOO(i, 1, n) {
        ll curDist = 0;
        int curNode = i;
        num[curNode]++;
        M00d(j, 19) {
            if(dist(ancestor[curNode][j], curNode) + curDist <= l) {
                curDist += dist(ancestor[curNode][j], curNode);
                curNode = ancestor[curNode][j];
                if(curNode == n) break;
            }
        }
        num[ancestor[curNode][0]]--;
    }
    dfs2(0);
    M00(i, n) {
        fout << ans[i] << "\n";
    }
}

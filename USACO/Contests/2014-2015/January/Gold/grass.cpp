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

int v, e;
const int MAX_V = 100000;
vi to[MAX_V];
vi from[MAX_V];
bool toHome[MAX_V]; //nodes that can go to root
bool fromHome[MAX_V]; //nodes that can be reached from root

stack<int> s;
int scc[MAX_V];
int sz[MAX_V];
int comp = 0;
bool visP1[MAX_V];
bool visP2[MAX_V];

vi toscc[MAX_V];
vi fromscc[MAX_V];

int dp[MAX_V];
bool vis[MAX_V];
int dp1[MAX_V];
int vis1[MAX_V];

void dfsto(int n) {
    if(toHome[n]) return;
    toHome[n] = 1;
    for(int u: from[n]) dfsto(u);
}

void dfsfrom(int n) {
    if(fromHome[n]) return;
    fromHome[n] = 1;
    for(int u: to[n]) dfsfrom(u);
}

void kosaP1(int n) {
    if(visP1[n]) return;
    visP1[n] = 1;
    for(int u: to[n]) kosaP1(u);
    s.push(n);
}

void kosaP2(int n) {
    if(visP2[n]) return;
    visP2[n] = 1;
    scc[n] = comp;
    for(int u: from[n]) kosaP2(u);
}

int dfs(int c) { //max path from 0 to n
    if(c == scc[0]) {
        dp[c] = 0;
        return 0;
    }
    if(vis[c]) return dp[c];
    vis[c] = 1;
    int ans = -10000000;
    for(int u: fromscc[c]) if(scc[u] != scc[c]) ans = max(ans, dfs(u));
    dp[c] = ans + sz[c];
    return dp[c];
}

int dfs1(int c) { //max path from n to 0
    if(c == scc[0]) {
        dp1[c] = 0;
        return 0;
    }
    if(vis1[c]) return dp1[c];
    vis1[c] = 1;
    int ans = -10000000;
    for(int u: toscc[c]) if(scc[u] != scc[c]) ans = max(ans, dfs1(u));
    dp1[c] = ans + sz[c];
    return dp1[c];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("grass.out");
    ifstream fin("grass.in");
    fin >> v >> e;
    M00(i, e) {
        int a, b; fin >> a >> b; a--; b--;
        to[a].PB(b);
        from[b].PB(a);
    }
    dfsto(0);
    dfsfrom(0);
    M00(i, v) kosaP1(i);
    while(!s.empty()) {
        int node = s.top(); s.pop();
        if(!visP2[node]) {
            kosaP2(node);
            comp++;
        }
    }
    M00(i, v) {
        sz[scc[i]]++;
    }
    M00(i, v) {
        for(int j: to[i]) toscc[scc[i]].PB(scc[j]);
        for(int j: from[i]) fromscc[scc[i]].PB(scc[j]);
    }
    //for each vertex in the scc graph, find max sum of sizes of verticies of a path from the vertex containing 1 to that vertex
    M00(i, comp) dfs(i);
    M00(i, comp) dfs1(i);
    int hi = 0;
    M00(i, v) {
        for(int j: to[i]) if(toHome[i] && fromHome[j]) {
           if(scc[i] != scc[j]) hi = max(hi, dp[scc[j]]+dp1[scc[i]]+sz[scc[0]]);
           else hi = max(hi, dp[scc[j]]+dp1[scc[i]]-sz[scc[i]]+sz[scc[0]]);
        }
        else {
            hi = max(hi, dp[scc[i]]+dp1[scc[j]]+sz[scc[0]]);
        }
    }
    fout << hi << "\n";
}

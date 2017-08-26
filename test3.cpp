/*
 ID: ldorian1
 LANG: C++11
 TASK: test3
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

#define MAX_N 100

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

vi graph[MAX_N];
int t = 0;
bool visited[MAX_N];
pi times[MAX_N];
vi rgraph[MAX_N];
int comp[MAX_N];
bool rvisited[MAX_N];
int c = 0;

void dfs(int s) {
    if(visited[s]) return;
    visited[s]=true;
    t++;
    F0R(i, graph[s].size()) {
        dfs(graph[s][i]);
    }
    t++;
    times[s].first=t;
}

void rdfs(int s, int c) {
    if(rvisited[s]) return;
    rvisited[s]=true;
    comp[s]=c;
    F0R(i, rgraph[s].size()) {
        rdfs(rgraph[s][i], c);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("test3.out");
    ifstream fin("test3.in");
    int n; fin >> n;
    F0R(i, n) {
        int k; fin >> k;
        F0R(j, k) {
            int a; fin >> a;
            graph[i].PB(a);
            rgraph[a].PB(i);
        }
    }
    F0R(i, n) {
        if(!visited[i]) dfs(i);
    }
    F0R(i, n) times[i].second=i;
    sort(begin(times), end(times), greater<pair<int, int>>());
    //F0R(i, n) cout << times[i].second << ": " << times[i].first << "\n";
    F0R(i, n) {
        int u = times[i].second;
        if(comp[u]==0) {
            c++;
            rdfs(u, c);
        }
    }
    F0R(i, n) {
        cout << i+1 << ": " << comp[i] << endl;
    }
}

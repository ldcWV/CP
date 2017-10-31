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

const int MAX_V = 250;
int v, e;
int weights[MAX_V][MAX_V];
int parent[MAX_V];
bool visited[MAX_V];
int dist[MAX_V];

int shortestPath() {
    bool vs[MAX_V];
    int d[MAX_V];
    M00(i, v) {
        vs[i] = 0;
        d[i] = 1000000000;
    }
    d[0] = 0;
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push(MP(0, 0));
    while(!pq.empty()) {
        int v1 = pq.top().S;
        pq.pop();
        if(vs[v1]) continue;
        vs[v1] = 1;
        M00(v2, v) {
            if(v1 != v2 && weights[v1][v2] != -1 && d[v2] > d[v1]+weights[v1][v2]) {
                d[v2] = d[v1]+weights[v1][v2];
                pq.push(MP(d[v2], v2));
            }
        }
    }
    return d[v-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("rblock.out");
    ifstream fin("rblock.in");
    fin >> v >> e;
    M00(i, MAX_V) M00(j, MAX_V) weights[i][j] = -1;
    M00(i, e) {
        int v1, v2; fin >> v1 >> v2; v1--; v2--;
        int dist; fin >> dist;
        weights[v1][v2] = dist;
        weights[v2][v1] = dist;
    }
    M00(i, v) parent[i] = -1;
    MOO(i, 1, v) dist[i] = 1000000000;
    
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push(MP(0, 0));
    while(!pq.empty()) {
        int v1 = pq.top().S;
        pq.pop();
        if(visited[v1]) continue;
        visited[v1] = 1;
        M00(v2, v) {
            if(v1 != v2 && weights[v1][v2] != -1 && dist[v2] > dist[v1]+weights[v1][v2]) {
                dist[v2] = dist[v1]+weights[v1][v2];
                pq.push(MP(dist[v2], v2));
                parent[v2] = v1;
            }
        }
    }
    int curr = v-1;
    vi path;
    while(curr != -1) {
        path.PB(curr);
        curr = parent[curr];
    }
    
    int hi = 0;
    M00(i, path.size()-1) {
        if(i != 0) {
            weights[path.at(i-1)][path.at(i)] /= 2;
            weights[path.at(i)][path.at(i-1)] /= 2;
        }
        weights[path.at(i+1)][path.at(i)] *= 2;
        weights[path.at(i)][path.at(i+1)] *= 2;
        hi = max(hi, shortestPath() - dist[v-1]);
    }
    fout << hi << "\n";
}

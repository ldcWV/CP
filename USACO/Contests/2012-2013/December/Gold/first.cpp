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
#include <unordered_set>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a) > 0) ? ((a)%(b)) : ((((a)+(b)*((-(a)/(b))+1))%b)))

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

const int MAX_N = 30000;
const int MAX_STRINGSUM = 300000;
int n;
string arr[MAX_N];

template<int SZ> struct trie {
    int t[SZ][26];
    bool mark[SZ][26];
    int cursz;
    bool perm[26];
    bool temp[26];
    trie() {
        M00(i, SZ) M00(j, 26) t[i][j] = -1;
        M00(i, SZ) M00(j, 26) mark[i][j] = 0;
        cursz = 1;
    }
    void insert(string k) {
        int cur = 0;
        M00(i, k.length()) {
            int v = k[i] - 'a';
            if(t[cur][v] == -1) t[cur][v] = cursz++;
            if(i == k.length()-1) mark[cur][v] = 1;
            cur = t[cur][v];
        }
    }
    bool visit(unordered_set<int> graph[26], int node) {
        if(perm[node]) return 1;
        if(temp[node]) return 0;
        temp[node] = 1;
        for(const int v: graph[node]) if(!visit(graph, v)) return 0;
        perm[node] = 1;
        return 1;
    }
    bool query(string k) {
        unordered_set<int> graph[26];
        int cur = 0;
        M00(i, k.length()) {
            int v = k[i] - 'a';
            M00(j, 26) if(j != v && t[cur][j] != -1) graph[v].insert(j);
            if(mark[cur][v] && i != k.length()-1) return 0;
            cur = t[cur][v];
        }
        M00(i, 26) perm[i] = 0, temp[i] = 0;
        M00(i, 26) {
            if(graph[i].size() && !perm[i] && !temp[i]) if(!visit(graph, i)) return 0;
        }
        return 1;
    }
};

int main() { FAST
    ofstream fout("first.out");
    ifstream fin("first.in");
    fin >> n;
    M00(i, n) fin >> arr[i];
    trie<300000> t;
    M00(i, n) t.insert(arr[i]);
    vector<string> a;
    M00(i, n) if(t.query(arr[i])) a.PB(arr[i]);
    fout << a.size() << "\n";
    M00(i, a.size()) fout << a[i] << "\n";
}

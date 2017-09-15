/*
 ID: ldorian1
 LANG: C++11
 TASK: maxflow
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
#define PMOD(a, b) (((a)+(b))%(b))

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 50000
#define MAX_K 100000
#define L2 17

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

struct Node {
    int ps = 0;
    int value;
    vector<Node*> children;
    Node* parent;
};

int n, k;
vi adjList[MAX_N];
pi queries[MAX_K];
Node* nodes[MAX_N];
bool used[MAX_N];
int tarr[MAX_N*2-1];
int tind = 0;
int cdepth = 0;

int IDind[MAX_N];
int tdepth[MAX_N*2-1];

int rmin[MAX_N*2-1][L2];

int val[MAX_N];
int currMax = 0;

void setup(Node* n) {
    int v = n->value;
    nodes[v] = n;
    used[v]=true;
    F0R(i, adjList[v].size()) if(!used[adjList[v].at(i)]) {
        Node* u = new Node();
        u->value = adjList[v].at(i);
        u->parent = n;
        n->children.PB(u);
        setup(u);
    }
}

void dfs(Node* n) {
    if(IDind[n->value]==-1) IDind[n->value]=tind;
    tdepth[tind]=cdepth;
    tarr[tind]=n->value;
    tind++;
    F0R(i, n->children.size()) {
        cdepth++;
        dfs(n->children.at(i));
        cdepth--;
        tarr[tind]=n->value;
        tdepth[tind]=cdepth;
        tind++;
    }
}

int LCA(int a, int b) {
    int i1 = IDind[a];
    int i2 = IDind[b];
    if(i1>i2) { //swap if not in correct order
        int temp = i2;
        i2 = i1;
        i1 = temp;
    }
    int l = i2-i1+1;
    int lg2 = 0;
    while((1<<(lg2+1))<l) lg2++;
    //we want to find index of min of tdepth in interval [i1, i2]
    int m;
    if(tdepth[rmin[i1][lg2]]<tdepth[rmin[i2-(1<<lg2)][lg2]]) m = rmin[i1][lg2];
    else m = rmin[i2-(1<<lg2)][lg2];
    return tarr[m];
}

int subtreeSum(Node* n) {
    int v = n->value;
    if(val[v]!=-1) return val[v];
    int s = n->ps;
    int sum = s;
    F0R(i, n->children.size()) sum+=subtreeSum(n->children.at(i));
    val[v]=sum;
    currMax=max(currMax,val[v]);
    return sum;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("maxflow.out");
    ifstream fin("maxflow.in");
    fin >> n >> k;
    F0R(i, n-1) {
        int u, v;
        fin >> u >> v;
        u--; v--;
        adjList[u].PB(v);
        adjList[v].PB(u);
    }
    F0R(i, k) fin >> queries[i].F >> queries[i].S;
    
    Node* root = new Node();
    root->value = 0;
    setup(root);
    F0R(i, n) IDind[i]=-1;
    dfs(root);
    
    Node* rRoot = new Node();
    root->parent = rRoot;
    rRoot->children.PB(root);
    rRoot->value = -1;
    
    F0R(i, n*2-1) {
        rmin[i][0] = i;
    }
    FOR(j, 1, L2) {
        F0R(i, n*2-1) if(i+(1<<j)<2*n) {
            if(tdepth[rmin[i][j-1]] < tdepth[rmin[i+(1<<(j-1))][j-1]]) rmin[i][j]=rmin[i][j-1];
            else rmin[i][j]=rmin[i+(1<<(j-1))][j-1];
        }
    }
    
    cout << LCA(4,5) << endl;
    
    F0R(i, k) {
        int p1 = queries[i].F;
        int p2 = queries[i].S;
        p1--;
        p2--;
        int lca = LCA(p1, p2);
        nodes[lca]->parent->ps--;
        nodes[lca]->ps--;
        nodes[p1]->ps++;
        nodes[p2]->ps++;
    }
    F0R(i, n) val[i]=-1;
    subtreeSum(root);
    /*F0R(i, n) {
        cout << i << ": " << nodes[i]->ps << " " << val[i] << endl;
    }
    cout << rRoot->ps << endl;*/
    fout << currMax << endl;
}

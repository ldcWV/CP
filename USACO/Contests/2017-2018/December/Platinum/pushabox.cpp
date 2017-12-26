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
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;

struct node {
    int x, y;
    vector<node*> adj;
    int depth;
    int highest;
    vector<int> bicomp;
    bool dn;
    bool up;
    bool lf;
    bool rt;
    node(int a, int b) {
        this->x = a;
        this->y = b;
        this->depth = -1;
        this->dn = 0;
        this->up = 0;
        this->lf = 0;
        this->rt = 0;
    }
};

const int MAX_N = 1510;
bool arr[MAX_N][MAX_N];
int n, m, q;
node* nodes[MAX_N][MAX_N];
bool used[MAX_N][MAX_N][4];
vector<pair<node*, node*>> comp;
int co;
int d;

bool gr(node* a, node* b) {
    if(a->x == b->x) return (a->y > b->y);
    return (a->x > b->x);
}

void makeComp(node* a, node* b) {
    co++;
    if(gr(a, b)) swap(a, b);
    while(comp[(int)comp.size()-1] != MP(a, b)) {
        pair<node*, node*> asdf = comp[(int)comp.size()-1];
        if(comp.size() == 0) return;
        comp.erase(comp.begin() + (int)comp.size()-1);
        asdf.F->bicomp.PB(co);
        asdf.S->bicomp.PB(co);
    }
    pair<node*, node*> asdf = comp[(int)comp.size()-1];
    comp.erase(comp.begin() + (int)comp.size()-1);
    asdf.F->bicomp.PB(co);
    asdf.S->bicomp.PB(co);
}

bool dfs(node* u, node* p) {
    node* a = u;
    node* b = p;
    if(gr(a, b)) swap(a, b);
    int dir = 0;
    if(a->x > b->x) dir = 1;
    if(a->y > b->y) dir = 2;
    if(a->y < b->y) dir = 3;
    if(!used[a->x][a->y][dir]) {
        comp.PB(MP(a, b));
        used[a->x][a->y][dir] = 1;
    }
    if(u->depth != -1) {
        p->highest = min(p->highest, u->depth);
        return 0;
    }
    u->depth = d++;
    u->highest = u->depth;
    bool hasMult = 0;
    for(node* v: u->adj) if(v != p && dfs(v, u)) {
        u->highest = min(u->highest, v->highest);
        if(u == p) {
            if(hasMult) {
                co++;
                makeComp(u, v);
            }
        } else {
            if(v->highest >= u->depth) {
                co++;
                makeComp(u, v);
            }
        }
        hasMult = 1;
    }
    return 1;
}

void addEdge(node* a, node* b) {
    a->adj.PB(b);
}

bool inBounds(int x, int y) {
    return ((x >= 0 && x < n) && (y >= 0 && y < m) && (!arr[x][y]));
}

void build() {
    M00(i, n) M00(j, m) if(inBounds(i, j) && nodes[i][j]->depth == -1) {
        dfs(nodes[i][j], nodes[i][j]);
        while(comp.size()) comp.erase(comp.begin() + (int)comp.size()-1);
    }
}

bool sameComp(node* a, node* b) {
    if(!a || !b) return 0;
    for(int i: a->bicomp) {
        for(int j: b->bicomp) if(j == i) return 1;
    }
    return 0;
}

void dfs2(int x, int y, int dir) {
    node* u = nodes[x][y];
    if(dir == 0 && u->lf) return;
    if(dir == 1 && u->rt) return;
    if(dir == 2 && u->up) return;
    if(dir == 3 && u->dn) return;
    if(dir == 0) u->lf = 1;
    if(dir == 1) u->rt = 1;
    if(dir == 2) u->up = 1;
    if(dir == 3) u->dn = 1;
    
    node* lf = inBounds(x, y-1) ? nodes[x][y-1] : nullptr;
    node* rt = inBounds(x, y+1) ? nodes[x][y+1] : nullptr;
    node* up = inBounds(x-1, y) ? nodes[x-1][y] : nullptr;
    node* dn = inBounds(x+1, y) ? nodes[x+1][y] : nullptr;
    if(dir == 0) { //coming from left
        if(inBounds(x, y+1)) dfs2(x, y+1, 0);
        if(sameComp(lf, rt)) dfs2(x, y, 1);
        if(sameComp(lf, up)) dfs2(x, y, 2);
        if(sameComp(lf, dn)) dfs2(x, y, 3);
    } else if(dir == 1) { //coming from right
        if(inBounds(x, y-1)) dfs2(x, y-1, 1);
        if(sameComp(rt, lf)) dfs2(x, y, 0);
        if(sameComp(rt, up)) dfs2(x, y, 2);
        if(sameComp(rt, dn)) dfs2(x, y, 3);
    } else if(dir == 2) { //coming from up
        if(inBounds(x+1, y)) dfs2(x+1, y, 2);
        if(sameComp(up, lf)) dfs2(x, y, 0);
        if(sameComp(up, rt)) dfs2(x, y, 1);
        if(sameComp(up, dn)) dfs2(x, y, 3);
    } else { //coming from down
        if(inBounds(x-1, y)) dfs2(x-1, y, 3);
        if(sameComp(dn, lf)) dfs2(x, y, 0);
        if(sameComp(dn, rt)) dfs2(x, y, 1);
        if(sameComp(dn, up)) dfs2(x, y, 2);
    }
}

bool vis[MAX_N][MAX_N];
pi bess;
pi box;

void dfs3(int i, int j) {
    if(vis[i][j]) return;
    if(arr[i][j]) return;
    if(i == box.F && j == box.S) return;
    vis[i][j] = 1;
    if(inBounds(i+1, j)) dfs3(i+1, j);
    if(inBounds(i-1, j)) dfs3(i-1, j);
    if(inBounds(i, j+1)) dfs3(i, j+1);
    if(inBounds(i, j-1)) dfs3(i, j-1);
}

int main() { FAST
    ofstream fout("pushabox.out");
    ifstream fin("pushabox.in");
    fin >> n >> m >> q;
    M00(i, n) {
        M00(j, m) {
            char c; fin >> c;
            if(c == '#') arr[i][j] = 1;
            else arr[i][j] = 0;
            if(c == 'A') bess = MP(i, j);
            else if(c == 'B') box = MP(i, j);
        }
    }
    M00(i, n) M00(j, m) if(inBounds(i, j)) nodes[i][j] = new node(i, j);
    M00(i, n) M00(j, m) if(inBounds(i, j)) {
        if(inBounds(i+1, j)) addEdge(nodes[i][j], nodes[i+1][j]);
        if(inBounds(i-1, j)) addEdge(nodes[i][j], nodes[i-1][j]);
        if(inBounds(i, j+1)) addEdge(nodes[i][j], nodes[i][j+1]);
        if(inBounds(i, j-1)) addEdge(nodes[i][j], nodes[i][j-1]);
    }
    build();
    dfs3(bess.F, bess.S);
    if(inBounds(box.F-1, box.S) && vis[box.F-1][box.S]) dfs2(box.F, box.S, 2);
    if(inBounds(box.F+1, box.S) && vis[box.F+1][box.S]) dfs2(box.F, box.S, 3);
    if(inBounds(box.F, box.S+1) && vis[box.F][box.S+1]) dfs2(box.F, box.S, 1);
    if(inBounds(box.F, box.S-1) && vis[box.F][box.S-1]) dfs2(box.F, box.S, 0);
    nodes[box.F][box.S]->lf = 1;
    M00(i, q) {
        int a, b; fin >> a >> b;
        a--; b--;
        node* u = nodes[a][b];
        if(u->lf || u->rt || u->up || u->dn) {
            fout << "YES\n";
        } else {
            fout << "NO\n";
        }
    }
}

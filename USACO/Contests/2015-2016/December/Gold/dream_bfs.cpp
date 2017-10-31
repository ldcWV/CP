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

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define MAX_N 1000
int n, m;
int arr[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N][2][4]; //x, y, smells, direction

struct Node{
    int x, y;
    int smell;
    int dir;
    Node(int x, int y, int s, int d) {
        this->x = x;
        this->y = y;
        this->smell = s;
        this->dir = d;
    }
};

bool poss(Node* asdf) {
    if(asdf->x < 0 || asdf->x == m || asdf->y < 0 || asdf->y == n) return 0;
    if(arr[asdf->x][asdf->y] == 0) return 0;
    if(asdf->smell == 0 && arr[asdf->x][asdf->y] == 3) return 0;
    return 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("dream.out");
    ifstream fin("dream.in");
    fin >> n >> m;
    M00(i, n) M00(j, m) fin >> arr[j][i];
    queue<pair<Node, int>> q;
    Node* start = new Node(0,0,0,0);
    q.push(MP(*start, 0));
    while(!q.empty()) {
        Node u = q.front().F; int dist = q.front().S; q.pop();
        while(!q.empty() && vis[u.x][u.y][u.smell][u.dir]) u = q.front().F, dist = q.front().S, q.pop();
        if(vis[u.x][u.y][u.smell][u.dir]) break;
        if(arr[u.x][u.y] != 4) {
            if(vis[u.x][u.y][u.smell][UP] || vis[u.x][u.y][u.smell][RIGHT] || vis[u.x][u.y][u.smell][DOWN] || vis[u.x][u.y][u.smell][LEFT]) continue;
        }
        vis[u.x][u.y][u.smell][u.dir] = 1;
        
        if(u.x == m-1 && u.y == n-1) {
            fout << dist << "\n";
            return 0;
        }
        if(arr[u.x][u.y] == 4) { //if purple
            if((u.dir == UP && (u.y == 0 || arr[u.x][u.y-1] == 0 || arr[u.x][u.y-1] == 3)) ||
               (u.dir == RIGHT && (u.x == n-1 || arr[u.x+1][u.y] == 0 || arr[u.x+1][u.y] == 3)) ||
               (u.dir == DOWN && (u.y == m-1 || arr[u.x][u.y+1] == 0 || arr[u.x][u.y+1] == 3)) ||
               (u.dir == LEFT && (u.x == 0 || arr[u.x-1][u.y] == 0 || arr[u.x-1][u.y] == 3))) { //if can't slide anymore
                Node* v = new Node(u.x, u.y-1, 0, UP); if(poss(v)) q.push(MP(*v, dist+1));
                v = new Node(u.x+1, u.y, 0, RIGHT); if(poss(v)) q.push(MP(*v, dist+1));
                v = new Node(u.x, u.y+1, 0, DOWN); if(poss(v)) q.push(MP(*v, dist+1));
                v = new Node(u.x-1, u.y, 0, LEFT); if(poss(v)) q.push(MP(*v, dist+1));
            }
            else { //continue sliding
                Node* v = new Node(u.x, u.y, 0, u.dir);
                if(u.dir == UP) v->y--;
                if(u.dir == RIGHT) v->x++;
                if(u.dir == DOWN) v->y++;
                if(u.dir == LEFT) v->x--;
                if(poss(v)) q.push(MP(*v, dist+1));
            }
            continue;
        }
        int newSmell = (arr[u.x][u.y] == 2) || u.smell;
        Node* v = new Node(u.x, u.y-1, newSmell, UP); if(poss(v)) q.push(MP(*v, dist+1));
        v = new Node(u.x+1, u.y, newSmell, RIGHT); if(poss(v)) q.push(MP(*v, dist+1));
        v = new Node(u.x, u.y+1, newSmell, DOWN); if(poss(v)) q.push(MP(*v, dist+1));
        v = new Node(u.x-1, u.y, newSmell, LEFT); if(poss(v)) q.push(MP(*v, dist+1));
    }
    fout << "-1\n"; return 0;
}

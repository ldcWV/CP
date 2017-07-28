/*
 ID: ldorian1
 LANG: C++11
 TASK: cownav
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

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define MAX_N 20

using namespace std;

int n, changeX[4] {1, 0, -1, 0}, changeY[4] {0, 1, 0, -1};
bool open[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N][MAX_N][MAX_N][4];
queue<tuple<int, int, int, int, int, int>> q;

bool outOfBounds(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= n || !open[x][y];
}

void addToQueue(int x1, int y1, int x2, int y2, int dir, int dis) {
    if(visited[x1][y1][x2][y2][dir]) return;
    q.push(make_tuple(x1, y1, x2, y2, dir, dis));
    visited[x1][y1][x2][y2][dir] = true;
}

int main() {
    ofstream fout("cownav.out");
    ifstream fin("cownav.in");
    fin >> n;
    F0Rd(y, n) {
        F0R(x, n) {
            char c;
            fin >> c;
            if(c == 'E') open[x][y] = true;
        }
    }
    q.push(make_tuple(0, 0, 0, 0, 0, 0));
    while(!q.empty()){
        tuple<int, int, int, int, int, int> state = q.front();
        q.pop();
        int x1 = get<0>(state);
        int y1 = get<1>(state);
        int x2 = get<2>(state);
        int y2 = get<3>(state);
        int dir = get<4>(state);
        int dis = get<5>(state);
        if(x1 == n - 1 && y1 == n - 1 && x2 == n - 1 && y2 == n - 1) {
            fout << dis << "\n";
            return 0;
        }
        addToQueue(x1, y1, x2, y2, (dir + 1) % 4, dis + 1);
        addToQueue(x1, y1, x2, y2, (dir + 3) % 4, dis + 1);
        
        int nx1 = x1 + changeX[dir];
        int ny1 = y1 + changeY[dir];
        int nx2 = x2 + changeX[(dir + 1) % 4];
        int ny2 = y2 + changeY[(dir + 1) % 4];
        if(outOfBounds(nx1, ny1) || x1 == n - 1 && y1 == n - 1) {nx1 = x1; ny1 = y1;}
        if(outOfBounds(nx2, ny2) || x2 == n - 1 && y2 == n - 1) {nx2 = x2; ny2 = y2;}
        addToQueue(nx1, ny1, nx2, ny2, dir, dis + 1);
    }
}

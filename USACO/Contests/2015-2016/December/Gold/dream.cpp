/*
 ID: ldorian1
 LANG: C++11
 TASK: dream
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

#define MT make_tuple
#define MP make_pair
#define F first
#define S second
#define LB lower_bound
#define UB upper_bound
#define PB push_back
#define MAX_N 1000

using namespace std;

int n, m;
int board[MAX_N][MAX_N];
int visited[MAX_N][MAX_N][2];
int dist[MAX_N][MAX_N][2];
pair<int, int> neighbors[4] {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int inBounds(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < m && board[x][y] != 0);
}

tuple<int, int, int> slide(int x, int y, int d) {
    int numMoves = 1;
    pair<int, int> currPos = {x, y};
    while(inBounds(currPos.F+neighbors[d].F, currPos.S+neighbors[d].S) && board[currPos.F][currPos.S]==4 && board[currPos.F+neighbors[d].F][currPos.S+neighbors[d].S]!=3) {
        numMoves++;
        currPos.F += neighbors[d].F;
        currPos.S += neighbors[d].S;
    }
    tuple<int, int, int> ans = MT(currPos.F, currPos.S, numMoves);
    return ans;
}

int main()
{
    ofstream fout("dream.out");
    ifstream fin("dream.in");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) fin >> board[i][j];
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> pq;
    pq.push(MT(0, 0, 0, 0));
    F0R(i, n) F0R(j, m) F0R(k, 2) dist[i][j][k] = 1000000000;
    dist[0][0][0] = 0;
    tuple<int, int, int> t = slide(0,1,1);
    while(!pq.empty()) {
        tuple<int, int, int, int> u = pq.top();
        pq.pop();
        int ux = get<2>(u);
        int uy = get<3>(u);
        int uSmells = get<1>(u);
        visited[ux][uy][uSmells]=1;
        F0R(i, 4) {
            pair<int, int> vPos = {ux + neighbors[i].F, uy + neighbors[i].S};
            int vx = vPos.F;
            int vy = vPos.S;
            if(inBounds(vx, vy)) {
                //if purple tile
                if(board[vx][vy]==4) {
                    tuple<int, int, int> f = slide(vx, vy, i);
                    int fx = get<0>(f);
                    int fy = get<1>(f);
                    int fd = get<2>(f);
                    int smell = (board[fx][fy] == 2);
                    if(!visited[fx][fy][smell] && dist[fx][fy][smell] > dist[ux][uy][uSmells] + fd) {
                        dist[fx][fy][smell] = dist[ux][uy][uSmells] + fd;
                        tuple<int, int, int, int> v = MT(dist[fx][fy][smell], smell, fx, fy);
                        pq.push(v);
                    }
                }
                //if orange tile
                else if(board[vx][vy] == 2) {
                    if(!visited[vx][vy][1] && dist[vx][vy][1] > dist[ux][uy][uSmells] + 1) {
                        dist[vx][vy][1] = dist[ux][uy][uSmells] + 1;
                        tuple<int, int, int, int> v = MT(dist[vx][vy][1], 1, vx, vy);
                        pq.push(v);
                    }
                }
                //if blue tile
                else if(board[vx][vy] == 3) {
                    if(uSmells && !visited[vx][vy][1] && dist[vx][vy][1] > dist[ux][uy][uSmells] + 1) {
                        dist[vx][vy][1] = dist[ux][uy][uSmells] + 1;
                        tuple<int, int, int, int> v = MT(dist[vx][vy][1], 1, vx, vy);
                        pq.push(v);
                    }
                }
                //if pink
                else {
                    if(!visited[vx][vy][uSmells] && dist[vx][vy][uSmells] > dist[ux][uy][uSmells] + 1) {
                        dist[vx][vy][uSmells]=dist[ux][uy][uSmells] + 1;
                        tuple<int, int, int, int> v = MT(dist[vx][vy][uSmells], uSmells, vx, vy);
                        pq.push(v);
                    }
                }
            }
        }
    }
    if(dist[n-1][m-1][0]!=1000000000 || dist[n-1][m-1][1]!=1000000000) {
        fout << min(dist[n-1][m-1][0], dist[n-1][m-1][1]) << endl;
        return 0;
    }
    fout << "-1" << endl;
}

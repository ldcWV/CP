/*
 ID: ldorian1
 LANG: C++11
 TASK: lasers
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
#define INT_MAX 2147483647
#define MAX_N 100000

using namespace std;

int n;
pair<int, int> barn; pair<int, int> laser;
pair<int, int> fencePos[MAX_N+2];
bool visited[2][MAX_N+2];
int dist[2][MAX_N+2];
vector<int> x0[MAX_N+2];
vector<int> x1[MAX_N+2];

template <class T1, class T2, class Pred = std::less<T2> >
struct sort_pair_second {
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(left.second, right.second);
    }
};

int main()
{
    //reading input
    ofstream fout("lasers.out");
    ifstream fin("lasers.in");
    fin >> n >> laser.first >> laser.second >> barn.first >> barn.second;
    F0R(i, n) {
        fin >> fencePos[i].first >> fencePos[i].second;
    }
    fencePos[n]={laser.first, laser.second};
    fencePos[n+1]={barn.first, barn.second};
    
    //condensing everything
    sort(fencePos, fencePos+n+2);
    int curr = 0;
    int prev = fencePos[0].first;
    fencePos[0].first=0;
    FOR(i, 1, n+2) {
        int a = fencePos[i].first;
        if(fencePos[i].first==prev) {
            if(fencePos[i].first==barn.first) barn.first=fencePos[i-1].first;
            if(fencePos[i].first==laser.first) laser.first=fencePos[i-1].first;
            fencePos[i].first=fencePos[i-1].first;
        }
        else {
            curr++;
            if(fencePos[i].first==barn.first) barn.first=curr;
            if(fencePos[i].first==laser.first) laser.first=curr;
            fencePos[i].first=curr;
        }
        prev = a;
    }
    sort(fencePos, fencePos+n+2, sort_pair_second<int, int>());
    curr = 0;
    prev = fencePos[0].second;
    fencePos[0].second=0;
    FOR(i, 1, n+2) {
        int a = fencePos[i].second;
        if(fencePos[i].second==prev) {
            if(fencePos[i].second==barn.second) barn.first=fencePos[i-1].second;
            if(fencePos[i].second==laser.second) laser.first=fencePos[i-1].second;
            fencePos[i].second=fencePos[i-1].second;
        }
        else {
            curr++;
            if(fencePos[i].second==barn.second) barn.second=curr;
            if(fencePos[i].second==laser.second) laser.second=curr;
            fencePos[i].second=curr;
        }
        prev = a;
    }
    
    F0R(i, n+2) {
        int a = fencePos[i].first;
        int b = fencePos[i].second;
        x0[a].push_back(b);
        x1[b].push_back(a);
    }
    /*F0R(i, n+2) {
        F0R(j, x0[i].size()) cout << i << ": " << x0[i].at(j) << endl;
    }*/
    
    //BFS
    queue<pair<int, int>> q; //first number determines vert/horiz, second determines location
    F0R(i, 2) F0R(j, n+2) dist[i][j]=1000000000;
    dist[0][laser.first]=0;
    dist[1][laser.second]=0;
    q.push({0, laser.first});
    q.push({1, laser.second});
    while(!q.empty()) {
        pair<int, int> u = q.front(); q.pop();
        while(!q.empty() && visited[u.first][u.second]) {
            u=q.front(); q.pop();
        }
        if(visited[u.first][u.second]) break;
        visited[u.first][u.second]=true;
        if((u.first==0 && u.second==barn.first) || (u.first==1 && u.second==barn.second)) {
            fout << min(dist[0][barn.first],dist[1][barn.second]) << endl;
            return 0;
        }
        if(u.first==0) {
            F0R(i, x0[u.second].size()) {
                pair<int, int> v = {1, x0[u.second].at(i)};
                if(dist[v.first][v.second]>dist[u.first][u.second]+1) {
                    dist[v.first][v.second]=dist[u.first][u.second]+1;
                    q.push(v);
                }
            }
        }
        else {
            F0R(i, x1[u.second].size()) {
                pair<int, int> v = {0, x1[u.second].at(i)};
                if(dist[v.first][v.second]>dist[u.first][u.second]+1) {
                    dist[v.first][v.second]=dist[u.first][u.second]+1;
                    q.push(v);
                }
            }
        }
    }
    fout << -1 << endl;
}

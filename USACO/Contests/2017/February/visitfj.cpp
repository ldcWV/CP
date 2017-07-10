/*
 ID: ldorian1
 LANG: C++11
 TASK:
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

using namespace std;

class Node
{
public:
    int x;
    int y;
    int d;
};

struct compare
{
    bool operator()(const pair<int, Node>& lhs, const pair<int, Node>& rhs)
    {
        return lhs.first > rhs.first;
    }
};

int n, t;
long long fieldTimes[100][100];
vector<Node> edgeList[100][300];

int main()
{
    ofstream fout("visitfj.out");
    ifstream fin("visitfj.in");
    fin >> n >> t;
    F0R(i, n) F0R(j, n) fin >> fieldTimes[i][j];
    //setting up the edgelist
    F0R(i, n) F0R(j, 3*n)
    {
        Node left, right, up, down;
        if(j%3==0)
        {
            left.y = j-2;
            right.y = j+4;
            up.y = j+1;
            down.y = j+1;
        }
        else if(j%3==1)
        {
            left.y = j-2;
            right.y = j+4;
            up.y = j+1;
            down.y = j+1;
        }
        else
        {
            left.y = j-5;
            right.y = j+1;
            up.y=j-2;
            down.y=j-2;
        }
        left.x=i;
        right.x=i;
        up.x=i-1;
        down.x=i+1;
        if(left.x>=0 && left.x<n && left.y>=0 && left.y<3*n)
        {
            left.d=t;
            if(j%3==2) left.d+=fieldTimes[left.x][left.y/3];
            edgeList[i][j].push_back(left);
        }
        
        if(right.x>=0 && right.x<n && right.y>=0 && right.y<3*n)
        {
            right.d=t;
            if(j%3==2) right.d+=fieldTimes[right.x][right.y/3];
            edgeList[i][j].push_back(right);
        }
        if(up.x>=0 && up.x<n && up.y>=0 && up.y<3*n)
        {
            up.d=t;
            if(j%3==2) up.d+=fieldTimes[up.x][up.y/3];
            edgeList[i][j].push_back(up);
        }
        if(down.x>=0 && down.x<n && down.y>=0 && down.y<3*n)
        {
            down.d=t;
            if(j%3==2) down.d+=fieldTimes[down.x][down.y/3];
            edgeList[i][j].push_back(down);
        }
    }
    
    //F0R(i, edgeList[1][5].size()) cout << edgeList[1][5].at(i).x << " " << edgeList[1][5].at(i).y << ": " << edgeList[1][5].at(i).d << endl; //debugging
    
    //dijkstra
    priority_queue<pair<int, Node>, vector<pair<int, Node>>, compare> pq;
    bool visited[n][3*n];
    int distance[n][3*n];
    F0R(i, n)
    {
        F0R(j, 3*n)
        {
            visited[i][j]=false;
            distance[i][j]=-1;
        }
    }
    Node source;
    source.x=0;
    source.y=0;
    distance[source.x][source.y]=0;
    pq.push({0, source});
    while(!pq.empty())
    {
        Node u = pq.top().second;
        pq.pop();
        visited[u.x][u.y]=true;
        F0R(i, edgeList[u.x][u.y].size()) //for all of u's neighbors
        {
            Node v = edgeList[u.x][u.y].at(i);
            if(!visited[v.x][v.y] && (distance[v.x][v.y]==-1 || distance[v.x][v.y]>distance[u.x][u.y]+v.d))
            {
                distance[v.x][v.y]=distance[u.x][u.y]+v.d;
                pq.push({distance[v.x][v.y], v});
            }
        }
    }
    fout << min(min(distance[n-1][3*(n-1)], distance[n-1][3*(n-1)+1]), distance[n-1][3*(n-1)+2]) << endl;
}

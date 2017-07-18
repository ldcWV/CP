/*
 ID: ldorian1
 LANG: C++11
 TASK: moocast
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
#define MAX_N 1000

using namespace std;

class Node{
public:
    int x;
    int y;
};

int numCows;
int edgeList[MAX_N][MAX_N];

int main()
{
    ofstream fout("moocast.out");
    ifstream fin("moocast.in");
    fin >> numCows;
    Node cowPos[numCows];
    F0R(i, numCows) fin >> cowPos[i].x >> cowPos[i].y;
    F0R(i, numCows) F0R(j, numCows) {
        edgeList[i][j]=pow(cowPos[i].x-cowPos[j].x,2)+pow(cowPos[i].y-cowPos[j].y,2);
    }
    int dist[numCows];
    bool intree[numCows];
    F0R(i, numCows)
    {
        dist[i]=1000000000;
        intree[i]=false;
    }
    int treeSize=1;
    int treeCost=0;
    intree[0]=true;
    F0R(j, numCows)
    {
        dist[j]=edgeList[0][j];
    }
    while(treeSize<numCows)
    {
        int closestNode=-1;
        int closestDist=1000000000;
        F0R(i, numCows) if(!intree[i])
        {
            if(dist[i]<closestDist)
            {
                closestNode=i;
                closestDist=dist[i];
            }
        }
        treeSize++; treeCost=max(treeCost,dist[closestNode]);
        intree[closestNode]=true;
        F0R(i, numCows)
        {
            if(dist[i]>edgeList[closestNode][i])
                dist[i]=edgeList[closestNode][i];
        }
    }
    fout << treeCost << endl;
}

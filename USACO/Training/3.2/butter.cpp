/*
 ID: ldorian1
 LANG: C++11
 TASK: butter
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

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

typedef pair<int, int> P;
struct Order
{
    bool operator()(P const& a, P const& b) const
    {
        return (a.first<b.first);
    }
};

int numPastures, numCows, numPaths;
const int maxNumCows=500;
const int maxNumPastures=800;
int populations[maxNumPastures];
vector<pair<int,int>> edgeList[maxNumPastures];
priority_queue< P, vector<P>, greater<P> > pq;

int main()
{
    //READING INPUT
    ofstream fout("butter.out");
    ifstream fin("butter.in");
    fin >> numCows >> numPastures >> numPaths;
    F0R(i, numPastures) populations[i]=0;
    F0R(i, numCows)
    {
    	int a;
    	fin >> a;
    	populations[a-1]++;
    }
    F0R(i, numPaths)
    {
    	int p1, p2, distance;
    	fin >> p1 >> p2 >> distance;
    	edgeList[p1-1].push_back({p2-1,distance});
    	edgeList[p2-1].push_back({p1-1,distance});
    }
    
    //DIJKSTRA WITH PRIORITY QUEUE
    int currMin=INT_MAX;
    F0R(source, numPastures)
    {
    	int distances[numPastures];
    	bool visited[numPastures];
    	pq.push({0,source});
    	F0R(i, numPastures) distances[i]=2000000, visited[i]=false;
    	distances[source]=0;
    	while(!pq.empty())
    	{
    		int u = pq.top().second;
    		pq.pop();
    		if(!visited[u])
    		{
    			visited[u]=true;
    			F0R(j, edgeList[u].size())
    			{
    				if(distances[edgeList[u].at(j).first]>distances[u]+edgeList[u].at(j).second)
    				{
    					distances[edgeList[u].at(j).first]=distances[u]+edgeList[u].at(j).second;
    					pq.push({distances[edgeList[u].at(j).first],edgeList[u].at(j).first});
    				}
    			}
    		}
    	}
    	int sum = 0;
    	F0R(i, numPastures) sum+=populations[i]*distances[i];
    	if(sum<currMin) currMin=sum;
    }
    fout << currMin << endl;
}
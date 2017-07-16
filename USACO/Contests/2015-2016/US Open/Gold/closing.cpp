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
vector<int> edgeList[200000];
int numNodes, numEdges;
int closeOrder[200000];
bool onBoard[200000];
vector<string> ans;
int parent[200000]; //tree[i] is parent of node i, parent is -1 if the node is the root

int component(int n) //returns the component of node n (the component of n is just n's parent's parent's parent's...)
{
    if(parent[n]!=n)
    {
        parent[n]=component(parent[n]);
    }
    return parent[n];
}

int hasNeighbor(int n)
{
    F0R(i, edgeList[n].size()) if(onBoard[edgeList[n].at(i)]) return edgeList[n].at(i);
    return -1;
}

int main()
{
    ofstream fout("closing.out");
    ifstream fin("closing.in");
    fin >> numNodes >> numEdges;
    F0R(i, numEdges)
    {
        int a, b; fin >> a >> b;
        a--; b--;
        edgeList[a].push_back(b);
        edgeList[b].push_back(a);
    }
    F0R(i, numNodes)
    {
        int a; fin >> a; a--;
        closeOrder[i]=a;
    }
    
    //add nodes to graph in reverse order and union them when necessary
    int numComponents=0;
    F0R(i, numNodes) parent[i]=i;
    F0Rd(i, numNodes)
    {
        int u = closeOrder[i]; //u is the node to be added
        onBoard[u]=true;
        numComponents++;
        if(hasNeighbor(u)!=-1) //if u has a neighbor that is on the board
        {
            int v = hasNeighbor(u); //v is a neighbor that is on the board
            numComponents--; //u is no longer alone
            parent[u]=component(v); //set u's parent to be v's component
            F0R(j, edgeList[u].size()) if(edgeList[u].at(j)!=v && onBoard[edgeList[u].at(j)]) //for its other neighbors
            {
                int k = edgeList[u].at(j); //k is a different neighbor
                if(component(k)!=component(u)) //if two neighbors are in different components
                {
                    parent[component(k)]=component(u); //merge the trees by making one tree's component's parent equal to the other tree's component
                    numComponents--;
                }
            }
        }
        //cout << numComponents << endl;
        if(numComponents==1) ans.push_back("YES");
        else ans.push_back("NO");
    }
    F0Rd(i, (int)(ans.size())) fout << ans.at(i) << endl;
}

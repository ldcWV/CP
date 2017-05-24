/*
 ID: ldorian1
 LANG: C++11
 TASK: agrinet
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647
#define MAX_FARMS 100

using namespace std;

int numFarms;
int conMatrix[MAX_FARMS][MAX_FARMS];
int treeCost=0;
int distances[MAX_FARMS];
bool intree[MAX_FARMS];
int treeSize=0;

int main()
{
    //READING INPUT
    //********************************************************************
    ofstream fout("agrinet.out");
    ifstream fin("agrinet.in");
    fin >> numFarms;
    F0R(i, numFarms) F0R(j, numFarms)
    {
        fin >> conMatrix[i][j];
    }
    
    //PRIM'S ALGORITHM
    //********************************************************************
    F0R(i, numFarms) distances[i]=INT_MAX;
    int source = 0;
    distances[source]=0;
    F0R(i, numFarms)
    {
        distances[i]=conMatrix[source][i];
    }
    while(treeSize<numFarms)
    {
        int currMin = INT_MAX;
        int currMinIndex = 0;
        F0R(i,numFarms)
        {
            if(!intree[i]&&distances[i]<=currMin)
            {
                currMin=distances[i];
                currMinIndex=i;
            }
        }
        intree[currMinIndex]=true;
        treeSize++;
        treeCost+=distances[currMinIndex];
        F0R(i, numFarms)
        {
            if(conMatrix[currMinIndex][i]<distances[i])
            {
                distances[i]=conMatrix[currMinIndex][i];
            }
        }
    }
    fout<<treeCost<<endl;
}

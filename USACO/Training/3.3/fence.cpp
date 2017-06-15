/*
 ID: ldorian1
 LANG: C++11
 TASK: fence
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

int numFences;
const int maxNumFences = 1024;
const int maxNumIntersections = 500;
vector<int> fenceList[maxNumIntersections];

int min(vector<int> a)
{
    int currMin=100000;
    F0R(i, a.size()) if(a.at(i)<currMin) currMin=a.at(i);
    return currMin;
}

int main()
{
    //READING INPUT
    ofstream fout("fence.out");
    ifstream fin("fence.in");
    fin >> numFences;
    F0R(i, numFences)
    {
        int a, b;
        fin >> a >> b;
        a--; b--; //0-based indexing system
        fenceList[a].push_back(b);
        fenceList[b].push_back(a);
    }
    
    //FINDING EULARIAN CYCLE
    stack<int> s;
    int start=0;
    F0R(i, 500) if(fenceList[i].size()%2==1)
    {
        start = i;
        break;
    }
    int pos=start; //start at intersection with odd degree
    vector<int> cycle;
    while(cycle.size()<numFences+1)
    {
        if(fenceList[pos].empty())
        {
            cycle.push_back(pos);
            if(s.empty()) break;
            pos=s.top();
            s.pop();
        }
        else
        {
            int oldPos = pos;
            int newPos = min(fenceList[oldPos]);
            s.push(oldPos);
            //deleting the edge
            fenceList[oldPos].erase(find(fenceList[oldPos].begin(), fenceList[oldPos].end(), newPos)); //erase newPos from neighbors of oldPos
            fenceList[newPos].erase(find(fenceList[newPos].begin(), fenceList[newPos].end(), oldPos)); //erase oldPos from neighbors of newPos
            pos = newPos;
        }
    }
    FORd(i,0,cycle.size()) fout << cycle.at(i)+1 << endl;
}

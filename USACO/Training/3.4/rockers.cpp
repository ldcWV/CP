/*
 ID: ldorian1
 LANG: C++11
 TASK: rockers
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

int numSongs, totalTime, numAlbums;
int songs[20];

vector<int> binary(long long num, int numDigits)
{
    vector<int> ans;
    int i = numDigits-1;
    while(num>0)
    {
        if(num%2==1) ans.push_back(i);
        num/=2;
        i--;
    }
    return ans;
}

bool works(vector<int> c)
{
    int total=0;
    int alb=0;
    F0R(i, (int)(c.size()))
    {
        if(songs[c.at(i)]>totalTime) return false;
        total+=songs[c.at(i)];
        if(total>totalTime)
        {
            total=songs[c.at(i)];
            alb++;
        }
        if(alb==numAlbums) return false;
    }
    return true;
}

int main()
{
    ofstream fout("rockers.out");
    ifstream fin("rockers.in");
    fin >> numSongs >> totalTime >> numAlbums;
    F0R(i, numSongs) fin >> songs[i];
    int currBest=0;
    F0Rd(i, pow(2,numSongs))
    {
        vector<int> combo = binary(i, numSongs);
        if(combo.size()>currBest)
        {
            if(works(combo)) currBest=combo.size();
        }
    }
    fout << currBest << endl;
}

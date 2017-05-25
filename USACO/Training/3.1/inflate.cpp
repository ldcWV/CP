/*
 ID: ldorian1
 LANG: C++11
 TASK: inflate
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

int totalTime;
int numCategories;
vector<pair<int,int>> categories; //categories[i].first is the number of points, categories[i].second is the time
int dparr[10001]; //dparr[i] is max value with i time left

int main()
{
    //READING INPUT
    //********************************************************************
    ofstream fout("inflate.out");
    ifstream fin("inflate.in");
    fin >> totalTime >> numCategories;
    F0R(i, numCategories)
    {
        pair<int,int> temp;
        fin >> temp.first >> temp.second;
        categories.push_back(temp);
    }
    
    //DP
    //********************************************************************
    F0R(i, totalTime+1)
    {
        int currMax=0;
        F0R(j, numCategories)
        {
            if(i-categories[j].second>=0&&categories[j].first+dparr[i-categories[j].second]>currMax)
                currMax=categories[j].first+dparr[i-categories[j].second];
        }
        dparr[i]=currMax;
    }
    
    //PRINTING OUTPUT
    //********************************************************************
    fout << dparr[totalTime] << endl;
}

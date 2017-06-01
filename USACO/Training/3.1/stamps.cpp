/*
 ID: ldorian1
 LANG: C++11
 TASK: stamps
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

int n, numStamps;
int stampValues[50];
vector<int> dp; //dp.at(i) is number of stamps for the best way for the stamps to add up to i

bool contains(int n) //returns whether n is in stampValues
{
    int min = 0;
    int max = numStamps;
    int middle = (min+max)/2;
    while(min+1!=max)
    {
        if(n>stampValues[middle]) min = middle;
        if(n==stampValues[middle]) return true;
        if(n<stampValues[middle]) max = middle;
        middle = (min+max)/2;
    }
    if(stampValues[middle]==n) return true;
    return false;
}

int main()
{
    ofstream fout("stamps.out");
    ifstream fin("stamps.in");
    fin >> n >> numStamps;
    F0R(i, 50) stampValues[i] = INT_MAX;
    F0R(i, numStamps) fin>>stampValues[i];
    sort(begin(stampValues),end(stampValues));
    int maxStamp = stampValues[numStamps-1];
    if(stampValues[0]!=1)
    {
        cout << 0 << endl;
        return 0;
    }
    dp.push_back(0);
    dp.push_back(1);
    int i = 1;
    while(true)
    {
        i++;
        if(contains(i))
        {
            dp.push_back(1);
            continue;
        }
        int currMin=INT_MAX;
        F0R(j, numStamps)
        {
            if(((int)(dp.size())-stampValues[j])>=0 && 1+dp.at(dp.size()-stampValues[j])<currMin)
            {
                currMin=1+dp.at(dp.size()-stampValues[j]);
            }
        }
        if(currMin>n) break;
        dp.push_back(currMin);
        if(dp.size()==20000) //the following trash here is used to conserve memory. do not follow my lead here as it is very bad practice
            //after submitting someone helped me realize a much better way would to just use mod 10000 -_- stupid me
        {
            vector<int> newDP;
            FOR(i, 10000, 20000) newDP.push_back(dp.at(i));
            dp.clear();
            FOR(i, 0, 10000) dp.push_back(newDP.at(i));
        }
    }
    fout << i-1 << endl;
}

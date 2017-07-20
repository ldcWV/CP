/*
 ID: ldorian1
 LANG: C++11
 TASK: cbarn
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

int arr[MAX_N];
bool taken[MAX_N];
int N;

int main()
{
    ofstream fout("cbarn.out");
    ifstream fin("cbarn.in");
    fin >> N; F0R(i, N) fin >> arr[i];
    int start = 0;
    int maxCows = 0;
    int currCows = 0;
    F0Rd(i, N)
    {
        currCows+=arr[i];
        currCows--;
        if(currCows>maxCows) {
            maxCows=currCows;
            start=i;
        }
    }
    long long total = 0;
    long long currTime = 0;
    long long currPos = start;
    long long numCowsLeft=N;
    F0R(i, N) taken[i]=false;
    queue<int> cows; //contains the times when the cows were picked up
    while(numCowsLeft>0)
    {
        F0R(i, arr[currPos]) cows.push(currTime);
        if(!cows.empty()&&!taken[currPos])
        {
            int t = cows.front();
            cows.pop();
            total+=pow(currTime-t,2);
            numCowsLeft--;
            taken[currPos]=true;
        }
        currTime++;
        currPos++; currPos=currPos%N;
    }
    fout << total << endl;
}

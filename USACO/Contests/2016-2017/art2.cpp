/*
 ID: ldorian1
 LANG: C++11
 TASK: art2
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
#define MAX_N 100000

using namespace std;

int n;
pair<int, int> intervals[MAX_N+1];
bool startPoint[MAX_N+1];
int endPoint[MAX_N+1];
int dp[MAX_N+1];
int p[MAX_N];

int main()
{
    ofstream fout("art2.out");
    ifstream fin("art2.in");
    fin >> n; F0R(i, n) fin >> p[i];
    F0R(i, n+1) {
        intervals[i].first=-1;
        intervals[i].second=-1;
    }
    F0R(i, n) {
        int k = p[i];
        if(intervals[k].first==-1) intervals[k].first=i;
        intervals[k].second=i;
    }
    F0R(i, n+1) {
        if(intervals[i].first!=-1 && p[intervals[i].first]!=0) startPoint[intervals[i].first]=true;
        if(intervals[i].second!=-1 && p[intervals[i].second]!=0) endPoint[intervals[i].second]=true;
    }
    int hi = 0;
    stack<int> s;
    F0R(i, n) {
        dp[i]=dp[i-1];
        if(i==0) dp[i]=0;
        if(i>0 && endPoint[i-1]) {
            dp[i]--;
            s.pop();
        }
        if(startPoint[i] && p[i]!=0) {
            dp[i]++;
            s.push(p[i]);
        }
        if((!s.empty() && p[i]==0) || (s.empty() && p[i]!=0) || (p[i]!=0 && !s.empty() && p[i]!=s.top())) {
            fout << "-1" << endl;
            return 0;
        }
        hi=max(hi, dp[i]);
    }
    fout << hi << endl;
}

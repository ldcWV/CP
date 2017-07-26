/*
 ID: ldorian1
 LANG: C++11
 TASK: circlecross
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
#define MAX_N 50000

using namespace std;

int n;
int BIT[2*MAX_N];
pair<int, int> ranges[MAX_N];

void update(int i, int v) {
    while(i<=2*n) {
        BIT[i]+=v;
        i += (i & -i);
    }
}

int sum(int s) {
    int total = 0;
    while(s>0) {
        total+=BIT[s];
        s -= (s & -s);
    }
    return total;
}

int rangeSum(int s, int e) {
    return sum(e)-sum(s);
}

int main() {
    ofstream fout("circlecross.out");
    ifstream fin("circlecross.in");
    fin >> n;
    F0R(i, n) {
        ranges[i].first = -1; ranges[i].second = -1;
    }
    F0R(i, 2*n) {
        int k; fin >> k; k--;
        if(ranges[k].first==-1) ranges[k].first=i;
        else ranges[k].second=i;
    }
    sort(begin(ranges), begin(ranges)+n);
    int total = 0;
    F0R(i, 2*n) {
        BIT[i]=0;
    }
    F0R(i, n) {
        total+=rangeSum(ranges[i].first, ranges[i].second);
        update(ranges[i].second,1);
    }
    fout << total << endl;
}

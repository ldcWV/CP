/*
 ID: ldorian1
 LANG: C++11
 TASK: mincross
 *

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
#include <cassert>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a)+(b))%(b))

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 100000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
pi s1[MAX_N];
pi s2[MAX_N];
int t[MAX_N];
int tree[MAX_N+5];

void add(int k, int x) {
    k++;
    while (k <= n) {
        tree[k] += x;
        k += k&-k;
    }
}

int sum(int k) {
    k++;
    int s = 0;
    while (k >= 1) {
        s += tree[k];
        k -= k&-k;
    }
    return s;
}

int rSum(int a, int b) { //sums from [a,b)
    return sum(b-1)-sum(a-1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("mincross.out");
    ifstream fin("mincross.in");
    fin >> n;
    F0R(i, n) fin >> s1[i].first;
    F0R(i, n) fin >> s2[i].first;
    F0R(i, n) s1[i].second=i;
    F0R(i, n) s2[i].second=i;
    pi s1o[MAX_N];
    F0R(i, n) s1o[i].first = s1[i].first;
    sort(begin(s1), begin(s1)+n);
    F0R(i, n) {
        t[i] = s1[s2[i].first-1].second;
    }
    ll numCrossings = 0;
    F0R(i, n) {
        add(t[i], 1);
        numCrossings+=rSum(t[i]+1, n);
    }
    ll currMin = numCrossings;
    F0Rd(i, n) {
        numCrossings -= n-t[i]-1;
        numCrossings += t[i];
        currMin = min(currMin, numCrossings);
    }
    
    sort(begin(s2), begin(s2)+n);
    F0R(i, n) {
        t[i] = s2[s1o[i].first-1].second;
    }
    F0Rd(i, n) {
        numCrossings -= n-t[i]-1;
        numCrossings += t[i];
        currMin = min(currMin, numCrossings);
    }
    fout << currMin << endl;
}

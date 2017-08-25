/*
 ID: ldorian1
 LANG: C++11
 TASK: split
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

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define MAX_N 50000
#define lMAX_N 16 //2^16 > MAX_N

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
pi pos[MAX_N];
int minX1[MAX_N]; int minX2[MAX_N];
int maxX1[MAX_N]; int maxX2[MAX_N];
int minY1[MAX_N]; int minY2[MAX_N];
int maxY1[MAX_N]; int maxY2[MAX_N];

void preprocess() {
    minX1[0]=pos[0].F; maxX1[0]=pos[0].F;
    minY1[0]=pos[0].S; maxY1[0]=pos[0].S;
    FOR(i, 1, n) {
        minX1[i]=min(minX1[i-1], pos[i].F);
        maxX1[i]=max(maxX1[i-1], pos[i].F);
        minY1[i]=min(minY1[i-1], pos[i].S);
        maxY1[i]=max(maxY1[i-1], pos[i].S);
    }
    minX2[n-1]=pos[n-1].F; maxX2[n-1]=pos[n-1].F;
    minY2[n-1]=pos[n-1].S; maxY2[n-1]=pos[n-1].S;
    F0Rd(i, n-1) {
        minX2[i]=min(minX2[i+1], pos[i].F);
        maxX2[i]=max(maxX2[i+1], pos[i].F);
        minY2[i]=min(minY2[i+1], pos[i].S);
        maxY2[i]=max(maxY2[i+1], pos[i].S);
    }
}

ll getArea(int k) { //get minimum rectangle area grouping first k and last n-k points
    ll width = (maxX1[k-1]-minX1[k-1]);
    ll height = (maxY1[k-1]-minY1[k-1]);
    ll a1 = width*height;
    width = (maxX2[k]-minX2[k]);
    height = (maxY2[k]-minY2[k]);
    ll a2 = width*height;
    return a1+a2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("split.out");
    ifstream fin("split.in");
    fin >> n;
    F0R(i, n) fin >> pos[i].F >> pos[i].S;
    
    
    ll currMin = 3000000000000000000;
    
    
    sort(begin(pos), begin(pos)+n);
    
    //F0R(i, n) cout << pos[i].F << " " << pos[i].S << endl;
    
    preprocess();
    ll totalArea = ((ll)(maxX1[n-1]-minX1[n-1]))*((ll)(maxY1[n-1]-minY1[n-1]));
    FOR(i, 1, n) {
        if(pos[i-1].first==pos[i].first) continue; //we only want to process each column once
        currMin=min(currMin, getArea(i));
    }
    
    //sort by y coords now
    F0R(i, n) {
        int a = pos[i].first;
        pos[i].first=pos[i].second;
        pos[i].second=a;
    }
    sort(begin(pos), begin(pos)+n);
    F0R(i, n) {
        int a = pos[i].first;
        pos[i].first=pos[i].second;
        pos[i].second=a;
    }
    
    
    preprocess();
    FOR(i, 1, n) {
        if(pos[i-1].second==pos[i].second) continue;
        currMin=min(currMin, getArea(i));
    }
    
    
    fout << totalArea-currMin << "\n";
}

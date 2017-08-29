/*
 ID: ldorian1
 LANG: C++11
 TASK: triangles
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

#define MAX_N 300

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
pi pos[MAX_N];
int numBelow[MAX_N][MAX_N];
int value[MAX_N];

bool below(int i, int j, int k) {
    int x1, y1, x2, y2;
    if(pos[i].F<pos[j].F) {
        x1 = pos[i].F;
        x2 = pos[j].F;
        y1 = pos[i].S;
        y2 = pos[j].S;
    }
    else {
        x1 = pos[j].F;
        x2 = pos[i].F;
        y1 = pos[j].S;
        y2 = pos[i].S;
    }
    int x = pos[k].F;
    int y = pos[k].S;
    if(x>=x1 && x<x2) {
        double m = ((double)(y2-y1))/((double)(x2-x1));
        double v = m*(double)(x-x1)+(double)(y1);
        if(y<v) return true;
    }
    return false;
}

int v(int a, int b, int c) {
    pi k[3];
    k[0]=pos[a];
    k[1]=pos[b];
    k[2]=pos[c];
    int lo = 0;
    int hi = 0;
    FOR(i, 1, 3) {
        if(k[i].F<k[lo].F) lo=i;
        if(k[i].F>k[hi].F) hi=i;
    }
    int neither = 0;
    F0R(i, 3) {
        if(i!=lo && i!=hi) neither=i;
    }
    if(lo==0) lo=a;
    else if(lo==1) lo=b;
    else if(lo==2) lo=c;
    if(hi==0) hi=a;
    else if(hi==1) hi=b;
    else if(hi==2) hi=c;
    if(neither==0) neither=a;
    else if(neither==1) neither=b;
    else if(neither==2) neither=c;
    int ans = abs(numBelow[lo][hi]-numBelow[lo][neither]-numBelow[hi][neither]);
    if(below(lo, hi, neither)) ans--;
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("triangles.out");
    ifstream fin("triangles.in");
    fin >> n;
    F0R(i, n) fin >> pos[i].F >> pos[i].S;
    F0R(i, n) F0R(j, n) if(i!=j) {
        if(pos[i].F==pos[j].F) continue;
        numBelow[i][j]=0;
        F0R(k, n) if(i!=k && j!=k) {
            if(below(i, j, k)) numBelow[i][j]++;
        }
    }
    F0R(i, n) {
        F0R(j, n) cout << numBelow[i][j] << " ";
        cout << endl;
    }
    F0R(i, n) value[i]=0;
    F0R(i, n) {
        FOR(j, i+1, n) {
            FOR(k, j+1, n)  { //for all triples of points
                int c = v(i,j,k);
                value[c]++;
            }
        }
    }
    F0R(i, n-2) {
        fout << value[i] << "\n";
    }
}

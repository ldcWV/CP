/*
 ID: ldorian1
 LANG: C++11
 TASK: lightsout
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

#define MAX_N 200

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
pi points[MAX_N];
int d[MAX_N];
int a[MAX_N];
int perimeter;

int dir(pi a1, pi a2, pi a3) {
    if((a2.S>a1.S && a3.F>a2.F) ||
       (a2.F>a1.F && a3.S<a2.S) ||
       (a2.S<a1.S && a3.F<a2.F) ||
       (a2.F<a1.F && a3.S>a2.S)) {
            return 1;
        }
    return 0;
}

int dist(int a) {
    int c = 0;
    F0R(i, a) {
        c+=d[i];
    }
    return min(c, perimeter-c);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("lightsout.out");
    ifstream fin("lightsout.in");
    fin >> n;
    F0R(i, n) fin >> points[i].first >> points[i].second;
    F0R(i, n) {
        d[i] = abs(points[i].first-points[(i+1)%n].first)+abs(points[i].second-points[(i+1)%n].second);
        perimeter+=d[i];
    }
    F0R(i, n) {
        a[i]=dir(points[(i-1+n)%n], points[i], points[(i+1)%n]);
    }
    int currMax = 0;
    FOR(k, 1, n) {
        vector<int> S;
        FOR(i, 1, n) if(i!=k && a[i]==a[k]) S.PB(i);
        int currDist = 0;
        int i = 0;
        while(!S.empty()) {
            if((k+i)%n==0) break;
            currDist+=d[(k+i)%n];
            F0Rd(j, (int)(S.size())) {
                if(d[(S.at(j)+i)%n]!=d[(k+i)%n] || a[(S.at(j)+i+1)%n]!=a[(k+i+1)%n]) {
                    S.erase(S.begin()+j);
                }
            }
            i++;
        }
        currDist+=dist((k+i)%n);
        currMax=max(currMax, currDist-dist(k));
    }
    fout << currMax << endl;
}

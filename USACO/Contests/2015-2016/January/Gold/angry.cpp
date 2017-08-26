/*
 ID: ldorian1
 LANG: C++11
 TASK: angry
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
#define MAX_N 50000

using namespace std;

int n;
int positions[MAX_N];
int l[MAX_N];
int r[MAX_N];

double getMinPower(long long a, long long b, long long d) { //gets minimum power needed to detonate a segment of length d with power a on the left and power b on the right
    double halfD = (double)(d)/2.0;
    double da = (double)(a)+1.0;
    double db = (double)(b)+1.0;
    if(a==0 && b==0) return halfD;
    if(a==0) return max(db, halfD);
    if(b==0) return max(da, halfD);
    return max(da, max(db, halfD));
}

bool works(double p) {
    int ra = p*2;
    int p2 = 0;
    F0R(p1, n) {
        while(p2<n && (p2<=p1 || positions[p2+1]-positions[p1]<=ra)) p2++;
        if(p2==p1==n-1) break;
        if(positions[p2]-positions[p1]<=ra && l[p1]+1<=p && r[p2]+1<=p) return true;
    }
    return false;
}

int main() {
    ofstream fout("angry.out");
    ifstream fin("angry.in");
      fin >> n;
    F0R(i, n) fin >> positions[i];
    sort(positions, positions+n);
    l[0]=0;
    int p2 = 0;
    FOR(p1, 1, n) {
        while(p2<p1-1 && max(positions[p1]-positions[p2], l[p2])>max(positions[p1]-positions[p2+1], l[p2+1]+1)) p2++;
        l[p1]=max(positions[p1]-positions[p2], l[p2]+1);
    }
    r[n-1]=0;
    p2 = n-1;
    F0Rd(p1, n-1) {
        while(p2>p1+1 && max(positions[p2]-positions[p1], r[p2]+1)>max(positions[p2-1]-positions[p1], r[p2-1]+1)) p2--;
        r[p1]=max(positions[p2]-positions[p1], r[p2]+1);
    }
    //F0R(i, n) cout << i << ": " << l[i] << " " << r[i] << endl;
    double ans = 0;
    for(int d = 1000000000/2; d>=1; d/=2) {
        while(ans+d<1000000000 && !works(ans+d)) ans+=d;
    }
    //for(double i = 0; i<=4; i+=.5) cout << i << ": " << works(i) << endl;
    if(works((double)(ans)+.5)) ans+=.5;
    else ans+=1;
    fout << fixed << setprecision(1);
    fout << round(ans*10)/10 << "\n";
}

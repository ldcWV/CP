/*
 ID: ldorian1
 LANG: C++11
 TASK: fortmoo
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
#include <map>

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

#define MAX_N 200

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, m;
int b[MAX_N][MAX_N];
int pref[MAX_N][MAX_N];

int sum(int x1, int x2, int y1, int y2) {
    if(x2<x1 || y2<y1) return 0;
    if(x1==0 && y1==0) return pref[x2][y2];
    if(x1==0) return pref[x2][y2]-pref[x2][y1-1];
    if(y1==0) return pref[x2][y2]-pref[x1-1][y2];
    return pref[x2][y2]-pref[x1-1][y2]-pref[x2][y1-1]+pref[x1-1][y1-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("fortmoo.out");
    ifstream fin("fortmoo.in");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) {
        char k; fin >> k;
        int k1 = (k=='.') ? 0 : 1;
        b[i][j]=k1;
    }
    pref[0][0]=b[0][0];
    FOR(i, 1, n) {
        pref[i][0]=pref[i-1][0]+b[i][0];
    }
    FOR(i, 1, m) {
        pref[0][i]=pref[0][i-1]+b[0][i];

    }
    FOR(i, 1, n) FOR(j, 1, m) pref[i][j]=b[i][j]+pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1];
    
    int hi = 0;
    F0R(x1, n) FOR(x2, x1, n) {
        bool g[m];
        F0R(j, m) g[j]=false;
        F0R(j, m) if(b[x1][j] || b[x2][j]) g[j]=true;
        int p1 = 0;
        while(true) {
            while(p1 < m && g[p1]==1) p1++;
            int p2 = p1; while(p2+1<m && g[p2+1]==0) p2++;
            int temp = p2;
            if(g[p1] || g[p2]) break;
            while(p1<=min(m-1,p2) && sum(x1,x2,p1,p1)!=0) p1++;
            while(p2>=max(0,p1) && sum(x1,x2,p2,p2)!=0) p2--;
            if(p2>=p1) {
                hi=max(hi, (x2-x1+1)*(p2-p1+1));
            }
            p1=temp+1;
            if(p1==n) break;
        }
    }
    fout << hi << "\n";
}

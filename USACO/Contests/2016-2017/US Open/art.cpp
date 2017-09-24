/*
 ID: ldorian1
 LANG: C++11
 TASK: art
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

#define MAX_N 1000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n;
int b[MAX_N][MAX_N];
pi ul[MAX_N*MAX_N];
pi br[MAX_N*MAX_N];
int diff[MAX_N][MAX_N];
int pref[MAX_N][MAX_N];
int w[MAX_N*MAX_N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("art.out");
    ifstream fin("art.in");
    fin >> n; F0R(i, n) F0R(j, n) fin >> b[i][j];
    bool used[n*n];
    F0R(i, n*n) used[i]=false;
    F0R(i, n) F0R(j, n) {
        if(b[i][j]!=0) used[b[i][j]-1]=true;
    }
    int numTypes=0;
    F0R(i, n*n) if(used[i]) numTypes++;
    if(numTypes==0) {
        fout << 0 << "\n";
        return 0;
    }
    if(numTypes==1) {
        fout << n*n-1 << "\n";
        return 0;
    }
    F0R(i, n*n) {
        ul[i]={10000,10000};
        br[i]={-1,-1};
    }
    F0R(i, n) F0R(j, n) if(b[i][j]!=0) {
        int k = b[i][j]-1;
        ul[k].F=min(ul[k].F, i);
        ul[k].S=min(ul[k].S, j);
        br[k].F=max(br[k].F, i);
        br[k].S=max(br[k].S, j);
    }
    F0R(i, n*n) if(ul[i].F!=10000) {
        diff[ul[i].F][ul[i].S]++;
        if(br[i].F<n-1) diff[br[i].F+1][ul[i].S]--;
        if(br[i].S<n-1) diff[ul[i].F][br[i].S+1]--;
        if(br[i].F < n-1 && br[i].S < n-1) diff[br[i].F+1][br[i].S+1]++;
    }
    pref[0][0]=diff[0][0];
    FOR(i, 1, n) pref[i][0] = pref[i-1][0]+diff[i][0];
    FOR(i, 1, n) pref[0][i] = pref[0][i-1]+diff[0][i];
    FOR(i, 1, n) FOR(j, 1, n) {
        pref[i][j]=diff[i][j]+pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1];
    }
    F0R(i, n) F0R(j, n) if(pref[i][j] >= 2) {
        w[b[i][j]-1]=true;
    }
    int count = 0;
    F0R(i, n*n) if(!w[i]) count++;
    fout << count << "\n";
}

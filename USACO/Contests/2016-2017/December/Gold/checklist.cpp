/*
 ID: ldorian1
 LANG: C++11
 TASK:
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
#define MAX_N 1001
#define SQ(N) (N)*(N)

using namespace std;

int H, G;
pair<int, int> hPos[MAX_N];
pair<int, int> gPos[MAX_N];
int minCost[MAX_N+1][MAX_N+1][2]; //minDist[i][j][k] is minimum cost to reach the first i holsteins, the first j guernseys, and end with a k (k=0 -> holstein, k=1 -> guernsey)

int hDist(int i, int j) { //distance between holstein i and holstein j
    i--; j--;
    return SQ(hPos[i].first-hPos[j].first)+SQ(hPos[i].second-hPos[j].second);
}

int gDist(int i, int j) { //distance between guernsey i and guernsey j
    i--; j--;
    return SQ(gPos[i].first-gPos[j].first)+SQ(gPos[i].second-gPos[j].second);
}

int hgDist(int i, int j) { //distance between holstein i and guernsey j
    i--; j--;
    return SQ(hPos[i].first-gPos[j].first)+SQ(hPos[i].second-gPos[j].second);
}

int f(int i, int j, int k) { //computes minCost[i][j][k]
    if(minCost[i][j][k]!=-1) return minCost[i][j][k];
    if(k%2==0) {//if we want it to be holstein turn
        minCost[i][j][k]=min(f(i-1,j,0)+hDist(i-1,i), f(i-1,j,1)+hgDist(i,j));
        return minCost[i][j][k];
    }
    //else if guernsey turn
    minCost[i][j][k]=min(f(i,j-1,0)+hgDist(i,j),f(i,j-1,1)+gDist(j-1,j));
    return minCost[i][j][k];
}

int main() {
    ofstream fout("checklist.out");
    ifstream fin("checklist.in");
    fin >> H >> G;
    F0R(i, H) fin >> hPos[i].first >> hPos[i].second;
    F0R(i, G) fin >> gPos[i].first >> gPos[i].second;
    F0R(i, H+1) F0R(j, G+1) {
        minCost[i][j][0]=-1;
        minCost[i][j][1]=-1;
    }
    F0R(i, G+1) {
        minCost[0][i][0]=1000000000;
        minCost[0][i][1]=1000000000;
    }
    minCost[1][0][0]=0;
    minCost[1][0][1]=0;
    FOR(i, 2, H+1) {
        minCost[i][0][1]=1000000000;
        minCost[i][0][0]=minCost[i-1][0][0]+hDist(i, i-1);
    }
    FOR(i, 2, G+1) {
        minCost[1][i][0]=1000000000;
    }
    minCost[1][1][1]=hgDist(1,1);
    FOR(i, 2, G+1) {
        minCost[1][i][1]=minCost[1][i-1][1]+gDist(i-1, i);
    }
    fout << f(H, G, 0) << endl;
}

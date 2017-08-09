/*
 ID: ldorian1
 LANG: C++11
 TASK: fencedin
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
#define infty 1000000000000000000
#define MAX_N 25000

typedef long long ll;

using namespace std;

int xDim, yDim;
int vert, horiz;
tuple<ll, ll, bool> fences[2*MAX_N+2];
ll hPos[MAX_N];
ll vPos[MAX_N];

int main()
{
    ofstream fout("fencedin.out");
    ifstream fin("fencedin.in");
    fin >> xDim >> yDim >> vert >> horiz;
    F0R(i, vert) fin >> vPos[i];
    F0R(i, horiz) fin >> hPos[i];
    sort(begin(vPos), begin(vPos)+vert);
    sort(begin(hPos), begin(hPos)+horiz);
    F0R(i, vert+1) {
        if(i>0 && i<vert) get<0>(fences[i])=vPos[i]-vPos[i-1];
        else if(i==0) get<0>(fences[i])=vPos[i];
        else get<0>(fences[i])=xDim-vPos[vert-1];
        get<1>(fences[i])=horiz+1;
        get<2>(fences[i])=true;
    }
    F0R(i, horiz+1) {
        if(i>0 && i<horiz) get<0>(fences[vert+1+i])=hPos[i]-hPos[i-1];
        else if(i==0) get<0>(fences[vert+1+i])=hPos[i];
        else get<0>(fences[vert+1+i])=yDim-hPos[horiz-1];
        get<1>(fences[vert+1+i])=vert+1;
        get<2>(fences[vert+1+i])=false;
    }
    sort(begin(fences), begin(fences)+horiz+vert+2);
    ll numHoriz = 0;
    ll numVert = 0;
    ll total = 0;
    F0R(i, horiz+vert+2) {
        ll s = get<0>(fences[i]);
        ll n = get<1>(fences[i]);
        bool v = get<2>(fences[i]);
        if(v) {
            ll needed = n-numHoriz;
            if(needed==horiz+1) {
                needed=horiz;
            }
            if(numVert==0) needed=n-1;
            total+=needed*s;
            numVert++;
        }
        else {
            ll needed = n-numVert;
            if(needed==vert+1) {
                needed=vert;
            }
            if(numHoriz==0) needed=n-1;
            total+=needed*s;
            numHoriz++;
        }
    }
    fout << total << endl;
}

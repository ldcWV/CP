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
#include <assert.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)
#define PMOD(a, b) (((a)+(b))%(b))

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int MAX_N = 3000000;
int n, k;
int num[MAX_N];
bool occ[MAX_N];

int main() { FAST
    ofstream fout("empty.out");
    ifstream fin("empty.in");
    fin >> n >> k;
    int total = 0;
    M00(i, k) {
        int x, y;
        ll a, b;
        fin >> x >> y >> a >> b;
        MOO(i, 1, y+1) {
            total += x;
            num[(i*a+b)%n] += x;
        }
    }
    int done = 0;
    int holding = 0;
    int currInd = 0;
    while(done < total) {
        holding += num[currInd];
        num[currInd] = 0;
        if(holding > 0 && !occ[currInd]) {
            occ[currInd] = 1;
            holding--;
            done++;
        }
        currInd++;
        currInd %= n;
    }
    M00(i, n) if(!occ[i]) {
        fout << i << "\n";
        return 0;
    }
}

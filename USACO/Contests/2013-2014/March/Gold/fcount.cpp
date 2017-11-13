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

const int MAX_N = 500;
int n;
pii arr[MAX_N+5];

bool poss(int ind) { //every vertex except i
    int par = 0;
    M00(i, n) if(i != ind) par += arr[i].F % 2;
    if(par%2 == 1) return 0;
    M00(i, n) if(i != ind) {
        int lhs = 0;
        int rhs = 0;
        M00(j, i+1) if(j != ind) lhs += arr[j].F;
        int k = (i > ind) ? i-1 : i;
        rhs += (k+1)*k;
        MOO(j, i+1, n) if(j != ind) {
            rhs += min(k+1, arr[j].F);
        }
        if(lhs > rhs) return 0;
    }
    return 1;
}

int main() { FAST
    ofstream fout("fcount.out");
    ifstream fin("fcount.in");
    fin >> n; n++;
    M00(i, n) fin >> arr[i].F;
    M00(i, n) arr[i].S = i+1;
    sort(arr, arr+n);
    reverse(arr, arr+n);
    vi b;
    M00(i, n) {
        if(poss(i)) b.PB(arr[i].S);
    }
    sort(b.begin(), b.end());
    fout << b.size() << "\n";
    M00(i, b.size()) fout << b.at(i) << "\n";
}

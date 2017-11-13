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

const int MAX_N = 100000;
int n;
int arr[MAX_N];

bool possible(double k) { //can you achieve an average <= k
    double narr[MAX_N];
    double total = 0;
    M00(i, n) narr[i] = arr[i] - k;
    M00(i, n) total += narr[i];
    //sum of the rest <= 0
    double hi = -10000;
    double curr = 0;
    MOO(i, 1, n-1) {
        curr = max(narr[i], curr + narr[i]);
        hi = max(hi, curr);
    }
    return (total-hi <= 0);
}

int main() { FAST
    ofstream fout("sabotage.out");
    ifstream fin("sabotage.in");
    fin >> n;
    M00(i, n) fin >> arr[i];
    double hi = 10000;
    double lo = 0;
    double mid = (hi+lo)/2;
    while(lo + 0.0001 < hi) {
        if(possible(mid)) hi = mid;
        else lo = mid;
        mid = (hi+lo)/2;
    }
    fout << fixed << setprecision(3) << mid << "\n";
}

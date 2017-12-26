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
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;

const ll MOD = 1000000007;
const int MAX_N = 100000;
int n;
int arr[MAX_N];

bool poss(int c) {
    vi a;
    M00(i, c-1) a.PB(arr[i]);
    sort(a.begin(), a.end());
    M00(i, a.size()) if(a[i] < i+1) return 0;
    return 1;
}

int main() { FAST
    ofstream fout("greedy.out");
    ifstream fin("greedy.in");
    fin >> n; M00(i, n) fin >> arr[i];
    M00(i, n) arr[i] = n - arr[i] - 1;
    int cur = 0;
    for(int jump = n; jump > 0; jump /= 2) {
        while(cur + jump < n && poss(cur + jump)) cur += jump;
    }
    fout << n - cur << "\n";
}

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

int n, k;
int arr[100000];
multiset<int> window;

int main() { FAST
    ofstream fout("lineup.out");
    ifstream fin("lineup.in");
    fin >> n >> k;
    M00(i, n) fin >> arr[i];
    int l = 0;
    int hi = 1;
    int sz = 0;
    M00(r, n) {
        window.insert(arr[r]); if(window.count(arr[r]) == 1) sz++;
        while(l < r && sz > k+1) {
            window.erase(window.find(arr[l]));
            if(window.count(arr[l++]) == 0) sz--;
        }
        hi = max(hi, (int)window.count(arr[r]));
    }
    fout << hi << "\n";
}

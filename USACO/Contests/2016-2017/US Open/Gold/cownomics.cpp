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
const int MAX_N = 500;

int n, length;

template<int SZ> struct rabinKarp {
    const ll mods[3] = {1000000007, 999119999, 1000992299};
    ll p[3][SZ];
    ll h[3][SZ];
    const ll base = 1000696969;
    rabinKarp() {}
    void build(string a) {
        M00(i, 3) {
            p[i][0] = 1;
            h[i][0] = (int)a[0];
            MOO(j, 1, (int)a.length()) {
                p[i][j] = (p[i][j-1] * mods[i]) % base;
                h[i][j] = (h[i][j-1] * mods[i] + (int)a[j]) % base;
            }
        }
    }
    tuple<ll, ll, ll> hsh(int a, int b) {
        if(a == 0) return make_tuple(h[0][b], h[1][b], h[2][b]);
        tuple<ll, ll, ll> ans;
        get<0>(ans) = (((h[0][b] - h[0][a-1]*p[0][b-a+1]) % base) + base) % base;
        get<1>(ans) = (((h[1][b] - h[1][a-1]*p[1][b-a+1]) % base) + base) % base;
        get<2>(ans) = (((h[2][b] - h[2][a-1]*p[2][b-a+1]) % base) + base) % base;
        return ans;
    }
};

ll toLL(tuple<ll, ll, ll> a) {
    return get<0>(a);
}

rabinKarp<MAX_N> spotty[MAX_N];
rabinKarp<MAX_N> normal[MAX_N];

bool works(int len) {
    M00(i, length - len + 1) {
        bool w = 1;
        unordered_set<ll> asdf;
        M00(j, n) asdf.insert(toLL(spotty[j].hsh(i, i+len-1)));
        M00(j, n) if(asdf.count(toLL(normal[j].hsh(i, i+len-1)))) w = 0;
        if(w) return 1;
    }
    return 0;
}

int main() {
    ofstream fout("cownomics.out");
    ifstream fin("cownomics.in");
    fin >> n >> length;
    M00(i, n) {
        string a; fin >> a;
        spotty[i].build(a);
    }
    M00(i, n) {
        string a; fin >> a;
        normal[i].build(a);
    }
    int currLen = 1;
    for(int jump = length; jump > 0; jump /= 2) {
        while(currLen + jump <= length && !works(currLen+jump)) currLen += jump;
    }
    fout << currLen + 1 << "\n";
}

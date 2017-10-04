/*
 ID: ldorian1
 LANG: C++11
 TASK: optmilk
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

#define MAX_N 40000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, d;
ll tree00[(1<<17)+1];
ll tree01[(1<<17)+1];
ll tree10[(1<<17)+1];
ll tree11[(1<<17)+1];
ll arr[MAX_N];

void updNode(int pos) {
    tree00[pos]=max(tree00[2*pos]+tree00[2*pos+1], max(tree00[2*pos]+tree10[2*pos+1], tree01[2*pos]+tree00[2*pos+1]));
    tree01[pos]=max(tree00[2*pos]+tree01[2*pos+1], max(tree00[2*pos]+tree11[2*pos+1], tree01[2*pos]+tree01[2*pos+1]));
    tree10[pos]=max(tree10[2*pos]+tree00[2*pos+1], max(tree10[2*pos]+tree10[2*pos+1], tree11[2*pos]+tree00[2*pos+1]));
    tree11[pos]=max(tree10[2*pos]+tree01[2*pos+1], max(tree10[2*pos]+tree11[2*pos+1], tree11[2*pos]+tree01[2*pos+1]));
    if(2*pos>=(1<<16)) tree11[pos]=-1000000000000;
}

void update(int pos, ll val) {
    pos += (1<<16);
    tree00[pos]=0;
    tree01[pos]=(pos%2==0) ? 0 : val;
    tree10[pos]=(pos%2==0) ? val : 0;
    tree11[pos]=val;
    pos/=2;
    while(pos>0) {
        updNode(pos);
        pos/=2;
    }
}

ll query() {
    return max(max(tree00[1], tree01[1]), max(tree10[1], tree11[1]));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("optmilk.out");
    ifstream fin("optmilk.in");
    
    fin >> n >> d;
    F0R(i, n) fin >> arr[i];
    F0R(i, n) update(i, arr[i]);
    ll ans = 0;
    F0R(i, d) {
        int p; ll v;
        fin >> p >> v;
        update(p-1, v);
        ans += query();
    }
    fout << ans << "\n";
}

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
int cow[2*MAX_N]; //stores name given index in concatenated string
int namelength[2*MAX_N];
ll ans[MAX_N];
int n;

template<int SZ> struct suffixArray {
    const static int LGSZ = 33-__builtin_clz(SZ-1);
    pair<pi, int> tup[SZ];
    int sortIndex[LGSZ][SZ];
    int res[SZ];
    int len;
    suffixArray(string s) {
        this->len = (int)s.length();
        M00(i, len) tup[i] = MP(MP((int)s[i], -1), i);
        sort(tup, tup+len);
        int temp = 0;
        tup[0].F.F = 0;
        MOO(i, 1, len) {
            if(s[tup[i].S] != s[tup[i-1].S]) temp++;
            tup[i].F.F = temp;
        }
        M00(i, len) sortIndex[0][tup[i].S] = tup[i].F.F;
        MOO(i, 1, LGSZ) {
            M00(j, len) tup[j] = MP(MP(sortIndex[i-1][j], (j+(1<<(i-1))<len)?sortIndex[i-1][j+(1<<(i-1))]:-1), j);
            sort(tup, tup+len);
            int temp2 = 0;
            sortIndex[i][tup[0].S] = 0;
            MOO(j, 1, len) {
                if(tup[j-1].F != tup[j].F) temp2++;
                sortIndex[i][tup[j].S] = temp2;
            }
        }
        M00(i, len) res[sortIndex[LGSZ-1][i]] = i;
    }
    int LCP(int x, int y) {
        int ox = x;
        int oy = y;
        if(x == y) return len - x;
        int ans = 0;
        M00d(i, LGSZ) {
            if(sortIndex[i][x] == sortIndex[i][y]) {
                x += (1<<i);
                y += (1<<i);
                ans += (1<<i);
            }
        }
        if(cow[ox+ans] != cow[ox] || cow[oy+ans] != cow[oy]) return min(namelength[ox], namelength[oy]);
        return ans;
    }
};

int main() { FAST
    ofstream fout("standingout.out");
    ifstream fin("standingout.in");
    string s = "";
    fin >> n;
    int temp = 0;
    M00(i, n) {
        string t; fin >> t;
        s += t;
        int temp2 = (int)t.length();
        M00(j, t.length()) {
            cow[temp] = i;
            namelength[temp] = temp2--;
            temp++;
        }
        cow[temp++] = -1;
        if(i != n-1) s += "$"; //dont want stuff to mess up with LCP
    }
    suffixArray<2*MAX_N> sa = suffixArray<2*MAX_N>(s);
    M00(i, s.length()) { //index in suffix array
        int ind = sa.res[i]; //index of suffix
        //MOO(i, ind, s.length()) cout << s[i];
        //cout << "\n";
        if(cow[ind] == -1) continue;
        ans[cow[ind]] += namelength[ind];
        int sub = 0;
        int r = i+1;
        while(r < s.length() && cow[sa.res[r]] == cow[ind]) r++;
        if(r < s.length() && cow[sa.res[r]] != cow[ind]) sub = max(sub, sa.LCP(sa.res[r], ind));
        if(i != 0 && cow[sa.res[i-1]] != -1 && cow[sa.res[i-1]] != cow[ind]) {
            int l = i-1;
            while(l > 0 && cow[sa.res[l]] != -1 && cow[sa.res[l]] == cow[ind]) l--;
            if(l >= 0 && cow[sa.res[l]] != -1 && cow[sa.res[l]] != cow[ind]) sub = max(sub, sa.LCP(sa.res[l], ind));
        } else if(i != 0 && cow[sa.res[i-1]] != -1) sub = max(sub, sa.LCP(sa.res[i-1], ind));
        ans[cow[ind]] -= sub;
        //cout << namelength[ind] - sub << "\n";
    }
    M00(i, n) fout << ans[i] << "\n";
}

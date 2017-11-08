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

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

int n;
const int MAX_N = 500;
pair<pii, bool> loc[MAX_N];
vector<pii> h;
int pref[1001][1001];

bool sortbysec(const pair<int,int> &a,
               const pair<int,int> &b)
{
    return (a.second < b.second);
}

int q(int x1, int x2, int y1, int y2) {
    int val = pref[x2][y2];
    if(x1 > 0) val -= pref[x1-1][y2];
    if(y1 > 0) val -= pref[x2][y1-1];
    if(x1 > 0 && y1 > 0) val += pref[x1-1][y1-1];
    return val;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("cowrect.out");
    ifstream fin("cowrect.in");
    fin >> n;
    M00(i, n) {
        int a, b; fin >> a >> b;
        pref[a][b] = 1;
        char c; fin >> c;
        if(c == 'G') {
            pref[a][b] = 600;
        }
        else {
            h.PB(MP(a, b));
        }
    }
    sort(h.begin(), h.end(), sortbysec);
    MOO(i, 1, 1001) pref[0][i] = pref[0][i-1] + pref[0][i];
    MOO(i, 1, 1001) pref[i][0] = pref[i-1][0] + pref[i][0];
    MOO(i, 1, 1001) MOO(j, 1, 1001) pref[i][j] = pref[i][j] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1];
    pii best = {0, 10000000};
    M00(i, h.size()) MOO(j, i, h.size()) if(q(0, 1000, h.at(i).S, h.at(j).S)%600 >= best.F) {
        int y1 = h.at(i).S;
        int y2 = h.at(j).S;
        vi t;
        M00(i, h.size()) if(h.at(i).S >= y1 && h.at(i).S <= y2) t.PB(h.at(i).F);
        sort(t.begin(), t.end());
        int i2 = 0;
        M00(k, t.size()) if(q(t.at(k), 1000, h.at(i).S, h.at(j).S)%600 >= best.F){
            int x1 = t.at(k);
            i2 = max(i2, k);
            int b = i2;
            while(i2+1 < t.size() && q(x1, t.at(i2+1), y1, y2) <= 500) {
                if(q(x1, t.at(i2+1), y1, y2) > q(x1, t.at(b), y1, y2)) b=i2+1;
                i2++;
            }
            int num = q(x1, t.at(b), y1, y2);
            if(num <= 500 && num > best.F) {
                best.F = num;
                best.S = (y2-y1)*(t.at(b)-x1);
            }
            else if(num <= 500 && num == best.F) {
                best.S = min(best.S,(y2-y1)*(t.at(b)-x1));
            }
        }
    }
    fout << best.F << "\n" << best.S << "\n";
}

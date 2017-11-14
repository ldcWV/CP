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

const int MAX_N = 50000;
int n;
pii p1[MAX_N];
pii p2[MAX_N];

bool cw(pii o, pii a, pii b) {
    return ((ll)(a.F-o.F)*(ll)(b.S-o.S)-(ll)(a.S-o.S)*(ll)(b.F-o.F) <= 0);
}

bool above(vector<pii> segs, pii pnt) {
    if(segs.size() == 1) return (pnt.F == segs.at(0).F && pnt.S >= segs.at(0).S);
    int k = (int)(lower_bound(segs.begin(), segs.begin()+segs.size(), pnt) - segs.begin());
    if(k == segs.size()) return false;
    if(segs[k].F == pnt.F) return pnt.S >= segs[k].S;
    if(k == 0) return false;
    pii a = segs[k-1];
    pii b = segs[k];
    //must be above a--b
    return ((ll)(pnt.S-a.S)*(ll)(b.F-a.F) >= (ll)(b.S-a.S)*(ll)(pnt.F-a.F));
}

bool below(vector<pii> segs, pii pnt) {
    if(segs.size() == 1) return (pnt.F == segs.at(0).F && pnt.S <= segs.at(0).S);
    int k = (int)(lower_bound(segs.begin(), segs.begin()+segs.size(), pnt) - segs.begin());
    if(k == segs.size()) return false;
    if(segs[k].F == pnt.F) return pnt.S <= segs[k].S;
    if(k == 0) return false;
    pii a = segs[k-1];
    pii b = segs[k];
    //must be below a--b
    return ((ll)(pnt.S-a.S)*(ll)(b.F-a.F) <= (ll)(b.S-a.S)*(ll)(pnt.F-a.F));
}

int main() { FAST
    ofstream fout("curling.out");
    ifstream fin("curling.in");
    fin >> n;
    M00(i, n) fin >> p1[i].F >> p1[i].S;
    M00(i, n) fin >> p2[i].F >> p2[i].S;
    sort(p1, p1+n);
    //upper and lower hulls
    vector<pii> up;
    vector<pii> dn;
    M00(i, n) {
        while(dn.size() >= 2 && cw(dn[dn.size()-2], dn[dn.size()-1], p1[i])) {
            dn.erase(dn.end()-1);
        }
        dn.PB(p1[i]);
    }
    M00d(i, n) {
        while(up.size() >= 2 && cw(up[up.size()-2], up[up.size()-1], p1[i])) {
            up.erase(up.end()-1);
        }
        up.PB(p1[i]);
    }
    sort(dn.begin(), dn.end());
    sort(up.begin(), up.end());
    if(dn[dn.size()-1].F == dn[dn.size()-2].F) dn.erase(dn.end()-1);
    if(up[0].F == up[1].F) up.erase(up.begin());
    
    //find all points above dn and below up
    int cnt1 = 0;
    M00(i, n) {
        if(above(dn, p2[i]) && below(up, p2[i])) cnt1++;
    }
    
    //repeat for other team
    sort(p2, p2+n);
    vector<pii> up1;
    vector<pii> dn1;
    M00(i, n) {
        while(dn1.size() >= 2 && cw(dn1[dn1.size()-2], dn1[dn1.size()-1], p2[i])) {
            dn1.erase(dn1.end()-1);
        }
        dn1.PB(p2[i]);
    }
    M00d(i, n) {
        while(up1.size() >= 2 && cw(up1[up1.size()-2], up1[up1.size()-1], p2[i])) {
            up1.erase(up1.end()-1);
        }
        up1.PB(p2[i]);
    }
    sort(dn1.begin(), dn1.end());
    sort(up1.begin(), up1.end());
    if(dn1[dn1.size()-1].F == dn1[dn1.size()-2].F) dn1.erase(dn1.end()-1);
    if(up1[0].F == up1[1].F) up1.erase(up1.begin());
    
    //find all points above dn and below up
    int cnt2 = 0;
    M00(i, n) {
        if(above(dn1, p1[i]) && below(up1, p1[i])) cnt2++;
    }
    fout << cnt1 << " " << cnt2 << "\n";
}

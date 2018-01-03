/*
 ID: ldorian1
 LANG: C++11
 TASK: roboherd
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
#include <cassert>

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

#define MAX_N 100000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, k;
int numModels[MAX_N];
vi models[MAX_N];
ll suffSum[MAX_N];
int c;
ll total = 0;

void count(ll cost, ll ub, int e) { //count number of possible cows less than ub, the sum so far is cost
    if(c >= k) return;
    if(numModels[e] > 1 && models[e][1] + cost + suffSum[e+1] >= ub) {
        c++;
        total += cost + models[e][0] + suffSum[e+1];
        return;
    }
    if(e == n-1) {
        M00(i, numModels[e]) {
            if(cost + models[e][i] < ub) {
                c++;
                total += cost + models[e][i];
            }
            else return;
        }
    } else {
        M00(i, numModels[e]) {
            if(cost + models[e][i] + suffSum[e+1] < ub) {
                count(cost + models[e][i], ub, e+1);
                if(c >= k) return;
            }
            else return;
        }
    }
}

bool comp(vi a1, vi a2) {
    M00(i, min((int)a1.size(), (int)a2.size())-1) {
        int d1 = a1[i+1] - a1[i];
        int d2 = a2[i+1] - a2[i];
        if(d1 != d2) return d1 < d2;
    }
    return ((int)a1.size() < (int)a2.size());
}

int main() { FAST
    ofstream fout("roboherd.out");
    ifstream fin("roboherd.in");
    fin >> n >> k;
    M00(i, n) {
        int temp;
        fin >> temp;
        M00(j, temp) {
            int c; fin >> c;
            models[i].PB(c);
        }
    }
    M00(i, n) sort(models[i].begin(), models[i].end());
    sort(models, models+n, comp);
    M00(i, n) numModels[i] = (int)models[i].size();
    suffSum[n-1] = models[n-1][0];
    M00d(i, n-1) suffSum[i] = suffSum[i+1] + models[i][0];
    c = 0;
    ll hi = (ll)1e13;
    ll lo = suffSum[0] + 1;
    ll mid = (hi+lo)/2;
    while(lo+1 < hi) {
        c = 0;
        count(0, mid, 0);
        if(c < k) lo = mid;
        else hi = mid;
        mid = (lo+hi)/2;
    }
    total = 0;
    c = 0;
    count(0, mid, 0);
    fout << total + (k-c) * mid << "\n";
}

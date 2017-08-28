/*
 ID: ldorian1
 LANG: C++11
 TASK:
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
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)


#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n = 10;
int treeSize=1;
int init = 0;

int op(int a, int b) {
    return a+b;
}

int query(int a, int b, int t[]) {
    a+=treeSize/2;
    b+=treeSize/2;
    int ans = init;
    while(a <= b) {
        if(a%2==1) ans = op(ans, t[a++]);
        if(b%2==0) ans = op(ans, t[b--]);
        a/=2; b/=2;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("test.out");
    ifstream fin("test.in");
    int arr[n];
    F0R(i, n) arr[i]=i;
    while(treeSize <= 2*n) treeSize*=2;
    int segTree[treeSize];
    FORd(i, 1, treeSize) {
        if(i>=treeSize/2+n) segTree[i]=init;
        else if(i>=treeSize/2) segTree[i]=arr[i-treeSize/2];
        else {
            segTree[i]=op(segTree[2*i],segTree[2*i+1]);
        }
    }
    int k = 0;
    int s = 0;
    FOR(i, 1, treeSize) {
        cout << segTree[i] << " ";
        if(s+(1<<k)==i) {
            cout << endl;
            s+=1<<k;
            k++;
        }
    }
    cout << query(3, 7, segTree) << endl;
}

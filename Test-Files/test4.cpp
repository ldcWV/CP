/*
 ID: ldorian1
 LANG: C++11
 TASK: test4
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

int treeSize=1;
int n;
int arr[14];
int s[1024];
int z[1024];

void update(int u, int a, int b, int k, int x, int y) {
    if(b<x || a>y) return;
    if(x>=a && y<=b) {
        z[k]+=u;
        return;
    }
    if(b>=y) {
        s[k]+=u*(y-a+1);
    }
    else {
        s[k]+=u*(a-x+1);
    }
    int d = (x+y)/2;
    update(u, a, b, 2*k, x, d);
    update(u, a, b, 2*k+1, d+1, y);
}

int sum(int a, int b, int k, int x, int y) {
    if(z[k]!=0) { //we might have to propagate it
        int height=floor(log2((double)(treeSize)))-floor(log2((double)(k)))-1;
        s[k]+=z[k]*pow(2,height);
        if(!(k>=n)) { //if it is not a leaf
            z[2*k]+=z[k];
            z[2*k+1]+=z[k];
        }
        z[k]=0;
    }
    if(b<x || a>y) return 0;
    if(x>=a && y<=b) return s[k];
    int d = (x+y)/2;
    return sum(a,b,2*k,x,d)+sum(a,b,2*k+1,d+1,y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("test4.out");
    ifstream fin("test4.in");
    fin >> n; F0R(i, n) fin >> arr[i];
    while(treeSize <= 2*n) treeSize*=2;
    FORd(i, 1, treeSize) {
        if(i>=treeSize/2+n) s[i]=0;
        else if(i>=treeSize/2) s[i]=arr[i-treeSize/2];
        else {
            s[i]=s[2*i]+s[2*i+1];
        }
    }
    update(3, 0, 1, 1, 0, treeSize/2-1);
    cout << sum(0, 2, 1, 0, treeSize/2-1) << endl;
}

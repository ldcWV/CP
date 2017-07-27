/*
 ID: ldorian1
 LANG: C++11
 TASK: bphoto
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

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define MAX_N 100000

using namespace std;

int n;
pair<int, int> nums[MAX_N];
int BIT[MAX_N+1], numInBIT;

void update(int i, int v) {
    numInBIT++;
    i++;
    while(i<=n) {
        BIT[i]+=v;
        i += (i&-i);
    }
}
int preSum(int k) {
    k++;
    int s = 0;
    while(k>0) {
        s+=BIT[k];
        k -= (k&-k);
    }
    return s;
}
bool unbal(int a, int b) {
    return(max(a,b)>2*min(a,b));
}

int main() {
    ofstream fout("bphoto.out");
    ifstream fin("bphoto.in");
    fin >> n;
    F0R(i, n) fin >> nums[i].first;
    F0R(i, n) nums[i].second=i;
    sort(nums, nums+n);
    int total = 0;
    F0Rd(i, n) {
        int left = preSum(nums[i].second - 1);
        int right = numInBIT - left;
        if(unbal(left,right)) {
            total++;
        }
        update(nums[i].second, 1);
    }
    fout << total << endl;
}

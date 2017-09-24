/*
 ID: ldorian1
 LANG: C++11
 TASK: cownomics
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
#define MAX_N 500

using namespace std;

string spotty[MAX_N];
string normal[MAX_N];
int n, length;

bool works(int seqLength) {
    F0R(i, length-seqLength+1) {
        set<string> s1;
        bool w = true;
        F0R(j, n) s1.insert(spotty[j].substr(i, seqLength));
        F0R(j, n) if(s1.count(normal[j].substr(i, seqLength))) w = false;
        if(w) return true;
    }
    return false;
}

int main()
{
    ofstream fout("cownomics.out");
    ifstream fin("cownomics.in");
    fin >> n >> length;
    F0R(i, n) fin >> spotty[i];
    F0R(i, n) fin >> normal[i];
    int d = 0;
    for(int jump = length/2; jump>=1; jump/=2) {
        while(d+jump<=length && !works(d+jump)) d+=jump;
    }
    fout << d+1 << "\n";
}

/*
 ID: ldorian1
 LANG: C++11
 TASK: fence9
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
#define INT_MAX 2147483647

using namespace std;

int a, b, p;

long gcd(int a, int b)
{
    if(a==b) return a;
    if(a==0) return b;
    if(b==0) return a;
    if(a<b) return gcd(a, b-a*(b/a));
    return gcd(a-b*(a/b), b);
}

long getNumLatticePoints(int a, int b) //a left, b up
{
    return gcd(a,b)+1;
}

int main()
{
    //trivial Pick's theorem
    ofstream fout("fence9.out");
    ifstream fin("fence9.in");
    fin >> a >> b >> p;
    long area = (p*b)/2;
    long tBP;
    if(p>a) tBP=p+getNumLatticePoints(a, b)+getNumLatticePoints(p-a, b)-2;
    else tBP=p+getNumLatticePoints(a, b)+getNumLatticePoints(a-p, b)-2;
    fout << area+1-tBP/2 << endl;
}

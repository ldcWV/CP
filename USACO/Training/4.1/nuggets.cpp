/*
 ID: ldorian1
 LANG: C++11
 TASK: nuggets
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
int numOffers;
int nuggets[10];
bool dparr[100000];

int gcd(int a, int b)
{
    if(b%a==0) return a;
    if(a%b==0) return b;
    if(a==b) return a;
    if(b>a) return gcd(a, b-a*(b/a));
    return gcd(a-b*(a/b), b);
}

int gcdAll(int a[], int num) //gcd of first num values in a
{
    int ans = a[0];
    F0R(i, num) ans = gcd(ans, a[i]);
    return ans;
}

int main()
{
    ofstream fout("nuggets.out");
    ifstream fin("nuggets.in");
    fin >> numOffers;
    F0R(i, numOffers) fin >> nuggets[i];
    if(gcdAll(nuggets, numOffers)!=1)
    {
        fout << "0" << endl;
        return 0;
    }
    int currMax=0;
    dparr[0]=true;
    F0R(i, 100000)
    {
        if(dparr[i])
        {
            F0R(j, numOffers)
            {
                if(i+nuggets[j]<100000) dparr[i+nuggets[j]]=true;
            }
        }
        else currMax=i;
    }
    fout << currMax << endl;
}

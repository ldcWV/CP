/*
 ID: ldorian1
 LANG: C++11
 TASK: kimbits
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

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

long long numBits, maxNum1s, n;
string ans = "";

long long choose(long long a, long long b) //a choose b
{
    if(b>a||b<0||a<0) return 0;
    long long answer = 1;
    FORd(i, a-b+1, a+1)
    {
        answer*=i;
        answer/=a-i+1;
    }
    return answer;
}

long long sumChoose(long long a, long long i, long long j) //a C (i) + a C (i+1) + a C (i+2) + ... + a C (j)
{
    long long sum = 0;
    FOR(k, i, j+1) sum+=choose(a,k);
    return sum;
}

int main()
{
    ofstream fout("kimbits.out");
    ifstream fin("kimbits.in");
    fin >> numBits >> maxNum1s >> n; n--;
    long long onesLeft = maxNum1s;
    long long min = 0;
    long long max = sumChoose(numBits, 0, onesLeft)-1;
    while(ans.length()<numBits)
    {
        long long sumIf0 = sumChoose(numBits-(long long)(ans.length())-1,0,onesLeft);
        long long sumIf1 = sumChoose(numBits-(long long)(ans.length())-1,0,onesLeft-1);
        if(min+sumIf0-1>=n)
        {
            ans+="0";
            max=min+sumIf0-1;
        }
        else
        {
            ans+="1";
            onesLeft--;
            min=min+sumIf0;
        }
    }
    fout << ans << endl;
}

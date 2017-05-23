/*
 ID: ldorian1
 LANG: C++11
 TASK: fracdec
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

using namespace std;

int num, denom;
string ans = "";
vector<int> used;
int a, b0, b1;
bool usedb0[9000000];

int indexOf(int a)
{
    F0R(i, used.size())
    {
        if(used.at(i)==a)
        {
            return i;
        }
    }
    return -1;
}

int numDigits(int number)
{
    if(number==0) return 1;
    int digits = 0;
    if (number < 0) digits = 1;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

int main()
{
    ofstream fout("fracdec.out");
    ifstream fin("fracdec.in");
    fin >> num >> denom;
    a = num/denom;
    ans+=to_string(a);
    ans+=".";
    b1 = denom*a;
    b0 = (num-b1)*10;
    used.push_back(b0);
    usedb0[b0]=true;
    bool repit = false;
    while(1)
    {
        if(b0==0)
        {
            break;
        }
        a=b0/denom;
        b1=denom*a;
        b0=(b0-b1)*10;
        ans+=to_string(a);
        if(usedb0[b0])
        {
            int t = indexOf(b0);
            ans.insert(ans.begin()+t+numDigits(num/denom)+1, '(');
            repit = true;
            break;
        }
        used.push_back(b0);
        usedb0[b0]=true;
    }
    if(repit)
    {
        ans+=")";
    }
    if(ans.back()=='.')
    {
        ans+="0";
    }
    F0R(i, ans.size())
    {
        if(i!=0&&i%76==0)
        {
            fout << endl;
        }
        fout << ans.substr(i,1);
    }
    fout << endl;
}

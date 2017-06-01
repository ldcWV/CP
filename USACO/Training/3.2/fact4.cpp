/*
 ID: ldorian1
 LANG: C++11
 TASK: fact4
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

const int maxN=4220;
int n;
int nums[maxN];
int numTrailingZeroes=0;

int deplete(int k) //removes all factors of 5 and updates numTrailingZeroes
{
    if(k%3125==0)
    {
        numTrailingZeroes+=5;
        return k/3125;
    }
    if(k%625==0)
    {
        numTrailingZeroes+=4;
        return k/625;
    }
    if(k%125==0)
    {
        numTrailingZeroes+=3;
        return k/125;
    }
    if(k%25==0)
    {
        numTrailingZeroes+=2;
        return k/25;
    }
    if(k%5==0)
    {
        numTrailingZeroes+=1;
        return k/5;
    }
    return k;
}

int main()
{
    ofstream fout("fact4.out");
    ifstream fin("fact4.in");
    fin >> n;
    F0R(i, n) nums[i]=i+1;
    F0R(i, n) nums[i]=deplete(nums[i]);
    int count = 0;
    if(n==1)
    {
        fout << 1 << endl; return 0;
    }
    if(n==2)
    {
        fout << 2 << endl; return 0;
    }
    if(n==3)
    {
        fout << 3 << endl; return 0;
    }
    //we have to keep track of last 2 digits. if first digit is odd, we have to carry over
    int last2Digits = 2;
    FOR(i, 2, n)
    {
        last2Digits=(last2Digits*nums[i])%100;
        if(count<numTrailingZeroes && last2Digits%2==0)
        {
            last2Digits/=2;
            count++;
        }
    }
    fout << last2Digits-10*(last2Digits/10) << endl;
}

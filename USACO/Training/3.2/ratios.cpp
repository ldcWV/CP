/*
 ID: ldorian1
 LANG: C++11
 TASK: ratios
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

tuple<int, int, int> goal;
tuple<int, int, int> mix1, mix2, mix3;
tuple<int, int, int> currBest;

tuple<int, int, int> combo(int a, int b, int c)
{
    tuple<int, int, int> ans;
    get<0>(ans) = get<0>(mix1)*a+get<0>(mix2)*b+get<0>(mix3)*c;
    get<1>(ans) = get<1>(mix1)*a+get<1>(mix2)*b+get<1>(mix3)*c;
    get<2>(ans) = get<2>(mix1)*a+get<2>(mix2)*b+get<2>(mix3)*c;
    return ans;
}

bool works(int a, int b, int c)
{
    tuple<int, int, int> k = combo(a, b, c);
    F0R(i, 100)
    {
        if(get<0>(k)==i*get<0>(goal)&&get<1>(k)==i*get<1>(goal)&&get<2>(k)==i*get<2>(goal)) return true;
    }
    return false;
}

int main()
{
    //READING INPUT
    ofstream fout("ratios.out");
    ifstream fin("ratios.in");
    fin >> get<0>(goal) >> get<1>(goal) >> get<2>(goal);
    fin >> get<0>(mix1) >> get<1>(mix1) >> get<2>(mix1);
    fin >> get<0>(mix2) >> get<1>(mix2) >> get<2>(mix2);
    fin >> get<0>(mix3) >> get<1>(mix3) >> get<2>(mix3);
    get<0>(currBest) = -1;
    get<1>(currBest) = -1;
    get<2>(currBest) = -1;
    
    //MAIN ALGORITHM (brute forces through all possible # of units of each mixture)
    F0R(a, 100) F0R(b, 100) F0R(c, 100)
    {
        if(a==0 && b==0 && c==0)
        {
            if(get<0>(goal)==0&&get<1>(goal)==0&&get<2>(goal)==0)
            {
                get<0>(currBest)=0;
                get<1>(currBest)=0;
                get<2>(currBest)=0;
                break;
            }
        }
        else if(works(a,b,c))
        {
            tuple<int, int, int> k = combo(a,b,c);
            if(get<0>(currBest)==-1 || get<0>(k)+get<1>(k)+get<2>(k) < get<0>(currBest)+get<1>(currBest)+get<2>(currBest))
            {
                get<0>(currBest)=a;
                get<1>(currBest)=b;
                get<2>(currBest)=c;
            }
        }
    }
    if(get<0>(currBest)==-1) fout << "NONE" << endl;
    else
    {
        fout << get<0>(currBest) << " " << get<1>(currBest) << " " << get<2>(currBest) << " " << (get<0>(currBest)*get<0>(mix1)+get<1>(currBest)*get<0>(mix2)+get<2>(currBest)*get<0>(mix3))/get<0>(goal) << endl;
    }
}

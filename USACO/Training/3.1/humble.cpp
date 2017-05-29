/*
 ID: ldorian1
 LANG: C++11
 TASK: humble
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
#include <assert.h>
#include <set>
//#include <ctime>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

const int maxNumPrimes = 100;
int numPrimes;
int N;
int primes[maxNumPrimes];
vector<long long> humbleNumbers;
int indexes[maxNumPrimes];

int main()
{
    //READING INPUT
    //*********************************************************************
    ofstream fout("humble.out");
    ifstream fin("humble.in");
    fin >> numPrimes >> N;
    F0R(i, maxNumPrimes) primes[i]=INT_MAX;
    F0R(i, numPrimes)
    {
        fin >> primes[i];
    }
    sort(primes, primes+maxNumPrimes);
    
    //MAIN ALGORITHM (one queue for each prime keeps track of the primes to be added (O(N*K))
    //*********************************************************************
    humbleNumbers.push_back(1);
    F0R(i, numPrimes) indexes[i]=0;
    while(humbleNumbers.size()!=N+1)
    {
        long long currMin=INT_MAX;
        int currMinIndex=0;
        F0R(i, numPrimes)
        {
            if(primes[i]*humbleNumbers.at(indexes[i])==humbleNumbers.at(humbleNumbers.size()-1))
            {
                indexes[i]++;
            }
            if(primes[i]*humbleNumbers.at(indexes[i])<currMin)
            {
                currMin=primes[i]*humbleNumbers.at(indexes[i]);
                currMinIndex=i;
            }
        }
        indexes[currMinIndex]++;
        humbleNumbers.push_back(currMin);
    }
    //F0R(i, humbleNumbers.size()) cout << humbleNumbers.at(i) << " ";
    fout << humbleNumbers.at(N) << endl;;
}

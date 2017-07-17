/*
 ID: ldorian1
 LANG: C++11
 TASK:
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

int N;
bool in[100000];

int main()
{
    //reading input and creating the arrays
    ofstream fout("cardgame.out");
    ifstream fin("cardgame.in");
    fin >> N;
    int oppFirst[N/2];
    int oppSecond[N/2];
    int bessFirst[N/2];
    int bessSecond[N/2];
    bool oppF[2*N]; bool oppS[2*N]; F0R(i, 2*N) {
        oppS[i]=false; oppF[i]=false;
    }
    F0R(i, N/2)
    {
        int k; fin >> k; k--;
        in[k]=true;
        oppF[k]=true;
    }
    F0R(i, N/2)
    {
        int k; fin >> k; k--;
        in[k]=true;
        oppS[k]=true;
    }
    int index0=0;
    int index1=0;

    F0R(i, 2*N)
    {
        if(oppF[i])
        {
            oppFirst[index0]=i;
            index0++;
        }
        if(oppS[i])
        {
            oppSecond[index1]=i;
            index1++;
        }
    }
    int index=0;
    F0R(i, 2*N)
    {
        if(!in[i])
        {
            if(index<N/2)
            {
                bessSecond[index]=i;
            }
            else {
                bessFirst[index-N/2]=i;
            }
            index++;
        }
    }
    
    //actual algorithm
    //first half of game
    int ans = 0;
    int k=-1;
    F0R(i, N/2) {
        k++; if(k>=N/2) break;
        while(bessFirst[k]<oppFirst[i]&&k<N/2-1) k++;
        if(bessFirst[k]>oppFirst[i]) ans++;
    }
    //second half of game
    k=N/2;
    F0Rd(i, N/2) {
        k--; if(k<0) break;
        while(bessSecond[k]>oppSecond[i]&&k>0) k--;
        if(bessSecond[k]<oppSecond[i]) ans++;
    }
    fout << ans << endl;
}

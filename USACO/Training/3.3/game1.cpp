/*
 ID: ldorian1
 LANG: C++11
 TASK: game1
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

int n;
int nums[100];
pair<int, int> dparr[101][101]; //dparr[i][j] contains the max score each player can obtain starting from when the game is at that state

pair<int, int> f(int a, int b)
{
	if(dparr[a][b].first!=-1 && dparr[a][b].second!=-1) return dparr[a][b];
	if((b-a)%2!=n%2) //if player 1's turn, we have to try to maximize player 1's score
	{
		if(nums[a]+f(a+1,b).first<nums[b]+f(a,b-1).first) //if taking from the right side is better
		{
			dparr[a][b].first=nums[b]+f(a,b-1).first;
			dparr[a][b].second=f(a,b-1).second;
			return dparr[a][b];
		}
		else //if taking from the left side is better
		{
			dparr[a][b].first=nums[a]+f(a+1,b).first;
			dparr[a][b].second=f(a+1,b).second;
			return dparr[a][b];
		}
	}
	else //if player 2's turn
	{
		if(nums[a]+f(a+1,b).second<nums[b]+f(a,b-1).second) //if taking from the right side is better
		{
			dparr[a][b].first=f(a,b-1).first;
			dparr[a][b].second=nums[b]+f(a,b-1).second;
			return dparr[a][b];
		}
		else //if taking from the left side is better
		{
			dparr[a][b].first=f(a+1,b).first;
			dparr[a][b].second=nums[a]+f(a+1,b).second;
			return dparr[a][b];
		}
	}
}

int main()
{
    ofstream fout("game1.out");
    ifstream fin("game1.in");
    fin >> n;
    F0R(i, n) fin >> nums[i];
    F0R(i, n) F0R(j, n)
    {
    	dparr[i][j].first=-1;
    	dparr[i][j].second=-1;
    }
    F0R(i, n)
    {
    	if(n%2==1) //if it's player 1's turn
    	{
    		dparr[i][i].first=nums[i];
    		dparr[i][i].second=0;
    	}
    	else
    	{
    		dparr[i][i].first=0;
    		dparr[i][i].second=nums[i];
    	}
    }
    fout << f(0,n-1).first << " " << f(0,n-1).second << endl;
}
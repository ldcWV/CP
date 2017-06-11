/*
 ID: ldorian1
 LANG: C++11
 TASK: spin
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

int speeds[5];
vector<pair<int,int>> wedges[5];
bool intervals[5][360][360]; //intervals[i][j][k] determines whether wheel i is open at j degrees after k seconds of rotating

bool between(int a, int b, int c) //checks whether a is between b and c on a circle
{
    a %=360; b%=360; c%=360;
    if(c<=b) c+=360;
    if(a<b) a+=360;
    if(a>=b && a<=c) return true;
    return false;
}

int main() //we just note that all the wheels will be back at the original position after 360 seconds
{
    //READING INPUT
    ofstream fout("spin.out");
    ifstream fin("spin.in");
    F0R(i, 5)
    {
        fin >> speeds[i];
        int numWedges;
        fin >> numWedges;
        F0R(j, numWedges)
        {
            int start, end;
            fin >> start >> end;
            end = start+end;
            wedges[i].push_back({start, end});
        }
    }
    
    //MAIN ALGORITHM (goes through each possible degree measure and records when each wheel lets a light through it at that degree at every time t, t is between 0 and 359)
    F0R(i, 5) F0R(j, 360)
    {
        F0R(t, 360)
        {
            bool ans = false;
            F0R(k, wedges[i].size())
            {
                if(between(j,wedges[i].at(k).first+speeds[i]*t,wedges[i].at(k).second+speeds[i]*t))
                {
                    ans = true;
                    break;
                }
            }
            intervals[i][j][t]=ans;
        }
    }
    F0R(t, 360)
    {
        F0R(j, 360) //for all degrees
        {
            bool ac = true;
            F0R(i, 5) //for all wheels
            {
                if(!intervals[i][j][t]) ac = false;
            }
            if(ac)
            {
                fout << t << endl;
                return 0;
            }
        }
    }
    fout << "none" << endl;
}

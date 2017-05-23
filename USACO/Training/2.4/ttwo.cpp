/*
 ID: ldorian1
 LANG: C++11
 TASK: ttwo
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
#define north {-1 ,0}
#define south {1, 0}
#define east {0, 1}
#define west {0,-1}

using namespace std;

template <typename T,typename U>
pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

int trees[10][10];
pair <int,int> farmerPos;
pair <int,int> cowPos;
pair <int,int> farmerDir;
pair <int,int> cowDir;

void turn(string a)
{
    pair <int,int> N = north;
    pair <int,int> S = south;
    pair <int,int> E = east;
    pair <int,int> W = west;
    if(a=="f")
    {
        if(farmerDir==N) farmerDir=east;
        else if(farmerDir==E) farmerDir=south;
        else if(farmerDir==S) farmerDir=west;
        else farmerDir=north;
    }
    else
    {
        if(cowDir==N) cowDir=east;
        else if(cowDir==E) cowDir=south;
        else if(cowDir==S) cowDir=west;
        else cowDir=north;
    }
}

void move()
{
    pair<int,int> tempF = farmerPos+farmerDir;
    if(tempF.first>=10 || tempF.second>=10 || tempF.first < 0 || tempF.second < 0 || trees[tempF.first][tempF.second]==1)
    {
        turn("f");
    }
    else
    {
        farmerPos=tempF;
    }
    
    pair<int,int> tempC = cowPos+cowDir;
    if(tempC.first>=10 || tempC.second>=10 || tempC.first < 0 || tempC.second < 0 || trees[tempC.first][tempC.second]==1)
    {
        turn("c");
    }
    else
    {
        cowPos=tempC;
    }
}

int main()
{
    ofstream fout("ttwo.out");
    ifstream fin("ttwo.in");
    F0R(i, 10)
    {
        string line;
        fin >> line;
        F0R(j, 10)
        {
            if(line.substr(j,1)=="*")
            {
                trees[i][j]=1;
            }
            else if(line.substr(j,1)=="C")
            {
                cowPos={i,j};
            }
            else if(line.substr(j,1)=="F")
            {
                farmerPos={i,j};
            }
        }
    }
    farmerDir=north, cowDir=north;
    F0R(i,5000000)
    {
        move();
        if(farmerPos==cowPos)
        {
            fout << i+1 << endl;
            return 0;
        }
    }
    fout << 0 << endl;
}

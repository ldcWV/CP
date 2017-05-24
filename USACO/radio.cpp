#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

template <typename T,typename U>
pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

pair<int,int> N = {0,1};
pair<int,int> S = {0,-1};
pair<int,int> E = {1,0};
pair<int,int> W = {-1,0};

int numFJPositions;
int numBessiePositions;
pair<int,int> FJPositions[1001];
pair<int,int> bessiePositions[1001];
int distances[1001][1001]; //distances[i][j] is distance between FJ and Bessie when they are at positions i and j
int dparr[1001][1001]; //dparr[i][j] is minimum energy needed starting from FJ position i and Bessie position j

int f(int i, int j) //returns minimum energy required to finish the journey when FJ is at position i and Bessie is at position j
{
    if(i>=numFJPositions || i<0 || j>=numBessiePositions || j<0)
    {
        return INT_MAX;
    }
    if(dparr[i][j]!=-1) return dparr[i][j];
    dparr[i][j]=distances[i][j]+min(f(i+1,j),min(f(i,j+1),f(i+1,j+1))); //current distance+minimum distance of the three possible ways it can proceed (only FJ moves, only Bessie moves, and both move)
    return dparr[i][j];
}

int main()
{
    //READING INPUT
    //******************************************************************************
    ofstream fout("radio.out");
    ifstream fin("radio.in");
    fin>>numFJPositions>>numBessiePositions;
    numFJPositions++; numBessiePositions++;
    fin>>FJPositions[0].first>>FJPositions[0].second;
    fin>>bessiePositions[0].first>>bessiePositions[0].second;
    FOR(i, 1, numFJPositions)
    {
        char direction;
        fin >> direction;
        switch(direction)
        {
            case 'N': FJPositions[i]=FJPositions[i-1]+N; break;
            case 'S': FJPositions[i]=FJPositions[i-1]+S; break;
            case 'E': FJPositions[i]=FJPositions[i-1]+E; break;
            case 'W': FJPositions[i]=FJPositions[i-1]+W; break;
        }
    }
    FOR(i, 1, numBessiePositions)
    {
        char direction;
        fin >> direction;
        switch(direction)
        {
            case 'N': bessiePositions[i]=bessiePositions[i-1]+N; break;
            case 'S': bessiePositions[i]=bessiePositions[i-1]+S; break;
            case 'E': bessiePositions[i]=bessiePositions[i-1]+E; break;
            case 'W': bessiePositions[i]=bessiePositions[i-1]+W; break;
        }
    }
    F0R(i, numFJPositions) F0R(j, numBessiePositions)
    {
        distances[i][j]=pow(FJPositions[i].first-bessiePositions[j].first,2)+pow(FJPositions[i].second-bessiePositions[j].second,2);
    }
    
    //DP
    //******************************************************************************
    F0R(i, numFJPositions) F0R(j, numBessiePositions) dparr[i][j]=-1;
    dparr[numFJPositions-1][numBessiePositions-1]=distances[numFJPositions-1][numBessiePositions-1];
    fout << f(0,0)-distances[0][0]<<endl;
}

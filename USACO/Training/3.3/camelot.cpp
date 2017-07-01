/*
 ID: ldorian1
 LANG: C++11
 TASK: camelot
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

const int MAX_R=30;
const int MAX_C=26;
const int MAX_KNIGHTS=MAX_R*MAX_C;
int r, c;
int numKnights=0;
int kX, kY; //position of king
string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int knightDist[MAX_C][MAX_R][MAX_C][MAX_R]; //[x1][y1][x2][y2] distance in knight moves
vector<pair<int,int>> knightPos;

int kingDist(int x1, int y1, int x2, int y2) //returns distance between (x1,y1) and (x2,y2) when king has to walk
{
    return max(abs(x1-x2),abs(y1-y2));
}

bool inBoard(int x, int y) //checks if (x,y) is in the board
{
    return x>=0 && x<c && y>=0 && y<r;
}

int main()
{
    //READING INPUT
    ofstream fout("camelot.out");
    ifstream fin("camelot.in");
    fin >> r >> c;
    char temp; fin >> temp;
    kX=(int)(alphabet.find(temp));
    F0R(w, c) F0R(x, r) F0R(y, c) F0R(z, r) knightDist[w][x][y][z]=10000;
    fin >> kY; kY--;
    
    //compute the knight distance between every 2 points on the board using BFS
    F0R(i, c)
    {
        F0R(j, r)
        {
            queue<vector<int>> bfs;
            vector<int> temp;
            temp.push_back(i);
            temp.push_back(j);
            temp.push_back(0);
            bfs.push(temp);
            knightDist[i][j][i][j]=0;
            bool visited[c][r];
            F0R(a, c) F0R(b, r) visited[a][b]=false;
            visited[i][j]=true;
            temp.clear();
            
            while(!bfs.empty())
            {
                //pop first element of it
                vector<int> f = bfs.front();
                bfs.pop();
                
                //add all neighbors to the queue
                int x1=f.at(0);
                int y1=f.at(1);
                int d=f.at(2);
                knightDist[i][j][x1][y1]=d;
                int x2, y2;
                
                x2=x1+2; y2=y1+1;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1+2; y2=y1-1;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1-2; y2=y1+1;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1-2; y2=y1-1;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1+1; y2=y1+2;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1+1; y2=y1-2;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1-1; y2=y1+2;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
                x2=x1-1; y2=y1-2;
                if(inBoard(x2,y2) && !visited[x2][y2])
                {
                    temp.push_back(x2); temp.push_back(y2); temp.push_back(d+1);
                    bfs.push(temp);
                    visited[x2][y2]=true;
                    temp.clear();
                }
            }
        }
    }
    
    while(fin >> temp)
    {
        //read in position of knight
        int col, row;
        col=(int)(alphabet.find(temp));
        fin >> row; row--; //0-based index system
        knightPos.push_back({col,row});
        numKnights++; //update total number of knights
    }
    
    if(numKnights==0)
    {
        fout << 0 << endl;
        return 0;
    }
    
    //for every possible position king walks to and every possible position of meeting, check if less than minimum
    int currMin=10000000;
    F0R(i, c) F0R(j, r) F0R(dx, c) F0R(dy, r)
    {
        int sum = 0;
        sum+=kingDist(kX, kY, i, j); //king needs to walk to his square
        if(sum>5) continue; //assume king has to walk <=5 steps (lol)
        //now try all the knights and see which one will carry the king and arrange the meeting the fastest
        int currBestKnight=0;
        FOR(k, 1, numKnights)
        {
            if(knightDist[knightPos.at(k).first][knightPos.at(k).second][i][j]-knightDist[knightPos.at(k).first][knightPos.at(k).second][dx][dy]<knightDist[knightPos.at(currBestKnight).first][knightPos.at(currBestKnight).second][i][j]-knightDist[knightPos.at(currBestKnight).first][knightPos.at(currBestKnight).second][dx][dy]) currBestKnight=k;
        }
        F0R(k, numKnights) if(k!=currBestKnight) sum+=knightDist[knightPos.at(k).first][knightPos.at(k).second][dx][dy];
        sum+=knightDist[knightPos.at(currBestKnight).first][knightPos.at(currBestKnight).second][i][j]+knightDist[i][j][dx][dy];
        if(sum<currMin) currMin=sum;
    }
    fout << currMin << endl;
}

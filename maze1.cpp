/*
 ID: ldorian1
 LANG: C++11
 TASK: maze1
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
#define pb push_back

#define MAX_WIDTH 38
#define MAX_HEIGHT 100
#define INT_MAX 2147483647

using namespace std;

int width;
int height;
char maze[2*MAX_WIDTH+1][2*MAX_HEIGHT+1];
vector<pair<int,int>> edgeList[MAX_WIDTH][MAX_HEIGHT]; //edgeList[i][j] is a vector of all pairs of coordinates adjacent to it
vector<pair<int, int>> openings;
int distances1[MAX_WIDTH][MAX_HEIGHT]; //distances1[i][j] is distances from first opening to (i,j)
int distances2[MAX_WIDTH][MAX_HEIGHT];

void dijkstra1(int sourceX, int sourceY)
{
    bool visited[width][height];
    F0R(i,width) F0R(j, height) visited[i][j]=false;
    bool doneVisiting=false;
    distances1[sourceX][sourceY]=0;
    while(!doneVisiting)
    {
        //find minimum unvisited vertex
        int X=0, Y=0;
        int currMinDistance=INT_MAX;
        F0R(i, width) F0R(j, height)
        {
            if(!visited[i][j]&&distances1[i][j]<=currMinDistance)
            {
                X=i;
                Y=j;
                currMinDistance=distances1[i][j];
            }
        }
        cout << X<< " "<<Y<<endl;
        visited[X][Y]=true;
        cout<<edgeList[X][Y].size()<<endl;
        F0R(i, edgeList[X][Y].size()) //for all of its neighbors
        {
            if(1+distances1[X][Y]<distances1[edgeList[X][Y].at(i).first][edgeList[X][Y].at(i).second])
            {
                distances1[edgeList[X][Y].at(i).first][edgeList[X][Y].at(i).second]=1+distances1[X][Y];
            }
        }
        doneVisiting=true;
        F0R(i, width) F0R(j, height) if(!visited[i][j]) doneVisiting=false;
    }
}

void dijkstra2(int sourceX, int sourceY)
{
    bool visited[width][height];
    F0R(i,width) F0R(j, height) visited[i][j]=false;
    bool doneVisiting=false;
    distances2[sourceX][sourceY]=0;
    while(!doneVisiting)
    {
        //find minimum unvisited vertex
        int X=0, Y=0;
        int currMinDistance=INT_MAX;
        F0R(i, width) F0R(j, height)
        {
            if(!visited[i][j]&&distances2[i][j]<=currMinDistance)
            {
                X=i;
                Y=j;
                currMinDistance=distances2[i][j];
            }
        }
        visited[X][Y]=true;
        F0R(i, edgeList[X][Y].size())
        {
            if(1+distances2[X][Y]<distances2[edgeList[X][Y].at(i).first][edgeList[X][Y].at(i).second])
            {
                distances2[edgeList[X][Y].at(i).first][edgeList[X][Y].at(i).second]=1+distances2[X][Y];
            }
        }
        doneVisiting=true;
        F0R(i, width) F0R(j, height) if(!visited[i][j]) doneVisiting=false;
    }
}


int main()
{
    //READING INPUT
    //************************************************************************************
    ofstream fout("maze1.out");
    ifstream fin("maze1.in");
    fin >> width >> height;
    fin.ignore();
    F0R(i, 2*height+1)
    {
        string line;
        getline(fin, line);
        while(line.length()!=2*width+1) line+=" ";
        F0R(j, 2*width+1) maze[j][i]=line[j];
    }
    
    //SETTING UP EDGE LIST
    //************************************************************************************

    for(int i = 1; i<2*width+1; i+=2)
    {
        for(int j = 1; j<2*height+1; j+=2) //for all squares
        {
            int x = (i-1)/2;
            int y = (j-1)/2;
            if(maze[i+1][j]==' ') //if there is no wall to the right
            {
                if(i!=2*width-1)
                {
                    edgeList[x][y].pb({x+1,y});
                }
                else
                {
                    openings.pb({x,y});
                }
            }
            if(maze[i-1][j]==' ') //if there is no wall to the left
            {
                if(i!=1)
                {
                    edgeList[x][y].pb({x-1,y});
                }
                else
                {
                    openings.pb({x,y});
                }            }
            if(maze[i][j+1]==' ') //if there is no wall above
            {
                if(j!=2*height-1)
                {
                    edgeList[x][y].pb({x,y+1});
                }
                else
                {
                    openings.pb({x,y});
                }
            }
            if(maze[i][j-1]==' ') //if there is no wall below
            {
                if(j!=1)
                {
                    edgeList[x][y].pb({x,y-1});
                }
                else
                {
                    openings.pb({x,y});
                }
            }
        }
    }
    
    //DIJKSTRA
    //************************************************************************************
    F0R(i, width) F0R(j, height) distances1[i][j]=INT_MAX, distances2[i][j]=INT_MAX;
    dijkstra1(openings.at(0).first,openings.at(0).second);
    dijkstra2(openings.at(1).first,openings.at(1).second);
    
    //SOLVING PROBLEM (get min for each index, then find overall max)
    int distances[width][height];
    F0R(i,width) F0R(j, height)
    {
        distances[i][j]=min(distances1[i][j],distances2[i][j]);
    }
    int currMax = 0;
    F0R(i,width) F0R(j,height) if(distances[i][j]>currMax) currMax=distances[i][j];
    fout << currMax+1 << endl;
}

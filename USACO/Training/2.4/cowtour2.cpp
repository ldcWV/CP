/*
 ID: ldorian1
 LANG: C++11
 TASK: cowtour
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
#define size(a) sizeof(a)/sizeof(a[0])

#define MAX_SIZE 150
#define INT_MAX 2147483647

using namespace std;

int numPastures;
double edgeWeights[MAX_SIZE][MAX_SIZE];
pair<double,double> positions[MAX_SIZE];
double distances[MAX_SIZE][MAX_SIZE];
int components[MAX_SIZE];

double distance(int pasture1, int pasture2)
{
    return sqrt(pow(positions[pasture1].first-positions[pasture2].first,2)+pow(positions[pasture1].second-positions[pasture2].second,2));
}

int doneFlooding()
{
    F0R(i, numPastures)
    {
        if(components[i]==-1)
        {
            return i;
        }
    }
    return -1;
}

void flood(int pasture, int component)
{
    if(components[pasture]==component) return;
    components[pasture]=component;
    F0R(i, numPastures)
    {
        if(edgeWeights[pasture][i]!=INT_MAX) //for all of its neighbors
        {
            flood(i,component);
        }
    }
}

int main()
{
    //READING INPUT
    //*********************************************************
    ofstream fout("cowtour.out");
    ifstream fin("cowtour.in");
    fin >> numPastures;
    F0R(i, MAX_SIZE) F0R(j, MAX_SIZE) edgeWeights[i][j]=INT_MAX;
    F0R(i, numPastures) //read in the positions
    {
        double tempX, tempY;
        fin >> tempX >> tempY;
        positions[i]={tempX,tempY};
    }
    F0R(i, numPastures)
    {
        string line; fin >> line;
        F0R(j, numPastures)
        {
            if(atoi(line.substr(j,1).c_str()))
            {
                edgeWeights[i][j]=distance(i,j);
            }
        }
    }
    F0R(i,numPastures) edgeWeights[i][i]=0;
    //**********************************************************
    
    //FLOYD-WARSHALL ALGORITHM
    //**********************************************************
    F0R(i, numPastures) F0R(j, numPastures) distances[i][j]=edgeWeights[i][j];
    F0R(k, numPastures) F0R(i, numPastures) F0R(j, numPastures)
    {
        if(distances[i][k]+distances[k][j]<distances[i][j])
        {
            distances[i][j]=distances[i][k]+distances[k][j];
        }
    }
    //**********************************************************
    
    //FLOOD FILL
    //**********************************************************
    F0R(i, numPastures) components[i]=-1;
    int f = doneFlooding();
    int numComponents = 0;
    while(f!=-1)
    {
        flood(f,numComponents);
        f=doneFlooding();
        numComponents++;
    }
    //**********************************************************
    
    
    //MAIN ALGORITHM
    //it tests every pair of pastures from 2 different components
    //and computes the distance between them+the max distance
    //between each pasture to another pasture in the same component
    
    //we also need to consider the possibility that the diameter
    //fits inside one component
    //**********************************************************
    double ans = INT_MAX;
    F0R(comp0, numComponents) F0R(comp1, numComponents) if(comp0!=comp1)
    {
        double diam0 = 0;
        //get diameter of first component
        F0R(i, numPastures) if(components[i]==comp0) F0R(j, numPastures) if(components[j]==comp0)
        {
            if(distances[i][j]>diam0)
            {
                diam0=distances[i][j];
            }
        }
        double diam1 = 0;
        //get diameter of second component
        F0R(i, numPastures) if(components[i]==comp1) F0R(j, numPastures) if(components[j]==comp1)
        {
            if(distances[i][j]>diam1)
            {
                diam1=distances[i][j];
            }
        }
        double currMin = INT_MAX;
        F0R(i, numPastures)
        {
            if(components[i]==comp0) //for all pastures with component 0
            {
                F0R(j, numPastures)
                {
                    if(components[j]==comp1) //for all pastures with component 1
                    {
                        //furthest distance from i in the same component
                        double currMax0 = 0;
                        F0R(k, numPastures)
                        {
                            if(components[k]==comp0&&distances[i][k]>currMax0)
                            {
                                currMax0=distances[i][k];
                            }
                        }
                        //furthest distance from j in the same component
                        double currMax1 = 0;
                        F0R(k, numPastures)
                        {
                            if(components[k]==comp1&&distances[j][k]>currMax1)
                            {
                                currMax1=distances[j][k];
                            }
                        }
                        //compute total distance
                        double dis = currMax0+currMax1+distance(i,j);
                        if(dis<currMin)
                        {
                            if(dis<diam0||dis<diam1)
                            {
                                dis = max(diam0, diam1);
                            }
                            currMin=dis;
                        }
                    }
                }
            }
        }
        if(currMin<ans)
        {
            ans=currMin;
        }
    }
    fout << fixed << setprecision(6) << ans << endl;
    //************************************************************
}

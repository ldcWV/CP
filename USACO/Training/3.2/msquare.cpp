/*
 ID: ldorian1
 LANG: C++11
 TASK: msquare
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

string desired;
string permutations[40320];
int edgeList[40320][3]; //edgelist[i] has the list of 3 results after trying the 3 operations on permutations[i]

string A(string n) //performs operation A (swaps top and bottom rows)
{
    string ans = "";
    F0Rd(i, 8) ans+=n.substr(i,1);
    return ans;
}

string B(string n) //performs operation B (right circular shift)
{
    string ans = "";
    ans+=n.substr(3,1);
    ans+=n.substr(0,3);
    ans+=n.substr(5,3);
    ans+=n.substr(4,1);
    return ans;
}

string C(string n) //performs operation C (clockwise rotation of middle 4 squares)
{
    string ans = "";
    ans+=n.substr(0,1);
    ans+=n.substr(6,1);
    ans+=n.substr(1,1);
    ans+=n.substr(3,1);
    ans+=n.substr(4,1);
    ans+=n.substr(2,1);
    ans+=n.substr(5,1);
    ans+=n.substr(7,1);
    return ans;
}

int binSearch(string a) //find index of a in permutations
{
    int min = 0;
    int max = 40320;
    int mid = (min+max)/2;
    while(min+1!=max)
    {
        if(stoi(permutations[mid])>stoi(a)) max=mid;
        else if(stoi(permutations[mid])<stoi(a)) min=mid;
        else if(stoi(permutations[mid])==stoi(a)) return mid;
        mid=(min+max)/2;
    }
    return min;
}

int main()
{
    //READING INPUT
    ofstream fout("msquare.out");
    ifstream fin("msquare.in");
    F0R(i, 8)
    {
        string a;
        fin >> a;
        desired+=a;
    }
    string curr = "12345678";
    F0R(i, 40320)
    {
        permutations[i]=curr;
        next_permutation(curr.begin(), curr.end());
    }
    
    //SETTING UP EDGELIST
    F0R(i, 40320)
    {
        edgeList[i][0]=binSearch(A(permutations[i]));
        edgeList[i][1]=binSearch(B(permutations[i]));
        edgeList[i][2]=binSearch(C(permutations[i]));
    }
    
    //BFS to get shortest path to desired place
    string ans = "";
    int parents[40320];
    F0R(i, 40320) parents[i]=-1;
    queue<int> Q;
    bool visited[40320];
    
    visited[0]=true;
    Q.push(0);
    
    while(!Q.empty())
    {
        int curr = Q.front();
        Q.pop();
        if(permutations[curr]==desired) break;
        F0R(i, 3)
        {
            if(!visited[edgeList[curr][i]])
            {
                visited[edgeList[curr][i]]=true;
                parents[edgeList[curr][i]]=curr;
                Q.push(edgeList[curr][i]);
            }
        }
    }
    //now backtrack from the desired value to the beginning
    int c=binSearch(desired);
    while(c!=0)
    {
        int k = parents[c];
        F0R(i, 3) if(edgeList[k][i]==c)
        {
            if(i==0) ans = "A" + ans;
            else if(i==1) ans = "B" + ans;
            else if(i==2) ans = "C" + ans;
        }
        c=k;
    }
    fout << ans.length() << endl << ans << endl;
}

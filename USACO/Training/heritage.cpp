/*
 ID: ldorian1
 LANG: C++11
 TASK: heritage
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

string in, pre;
vector<string> hashTable;
int leftChild[26];
int rightChild[26];
string ans = "";

bool contains(vector<string> h, string a)
{
    F0R(i, h.size()) if(h.at(i)==a) return true;
    return false;
}

int hashh(string a)
{
    F0R(i, hashTable.size()) if(hashTable.at(i)==a) return i;
    return 0;
}

int solve(int startIn, int endIn, int startPre, int endPre) //this returns the root
{
    int root = hashh(pre.substr(startPre,1));
    int leftSize = (int)(in.find(pre.substr(startPre,1)))-startIn;
    int rightSize = endIn-startIn-leftSize;
    if(leftSize==0 && rightSize==0) return root;
    if(leftSize>0) leftChild[root]=solve(startIn, startIn+leftSize-1, startPre+1, startPre+leftSize);
    if(rightSize>0) rightChild[root]=solve(startIn+leftSize+1, startIn+leftSize+rightSize, startPre+leftSize+1, startPre+leftSize+rightSize);
    return root;
}

void print(int node)
{
    if(leftChild[node]!=-1) print(leftChild[node]);
    if(rightChild[node]!=-1) print(rightChild[node]);
    ans += hashTable.at(node);
}

int main()
{
    ofstream fout("heritage.out");
    ifstream fin("heritage.in");
    fin >> in >> pre;
    F0R(i, int(in.size()))
    {
        if(!contains(hashTable,in.substr(i,1))) hashTable.push_back(in.substr(i,1));
    }
    F0R(i, 26)
    {
        leftChild[i]=-1;
        rightChild[i]=-1;
    }
    solve(0, (int)(in.size())-1, 0, (int)(pre.size())-1);
    print(hashh(pre.substr(0,1)));
    fout << ans << endl;
}

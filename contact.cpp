/*
 ID: ldorian1
 LANG: C++11
 TASK: contact
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
#include <ctime>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

int toDec(string a) //O(a.length())
{
    int ans = 0;
    F0Rd(i, a.length()) if(a.substr(i,1)=="1")
    {
        ans+=pow(2,a.length()-i-1);
    }
    return ans;
}

string toBase2(int a, int numDigits) //O(log a)
{
    string ans = "";
    while(a!=0)
    {
        ans=to_string(a%2)+ans;
        a=a/2;
    }
    FOR(i, ans.length(), numDigits)
    {
        ans = "0" + ans;
    }
    return ans;
}

bool compare(string a, string b)
{
    if(a.length()<b.length()) return true;
    if(a.length()>b.length()) return false;
    return toDec(a)<toDec(b);
}

bool contains(vector<string> a, string b)
{
    F0R(i, a.size()) if(a.at(i)==b) return true;
    return false;
}

int minLength, maxLength, N;
const int maxChars = 200000;
const int maxN = 50;
const int maxL = 12;
string sequence;
int seqLength = 0;
vector<string> buckets[maxChars+1];

int main()
{
    //READING INPUT
    //*************************************jm**************************
    ofstream fout("contact.out");
    ifstream fin("contact.in");
    fin >> minLength >> maxLength >> N;
    
    while(fin)
    {
        string a;
        fin >> a;
        sequence += a;
        seqLength+=a.length();
    }
    
    //MAIN ALGORITHM
    //pointer goes through array and every time it moves, it records the digits of length minLength to maxLength in front of int and updates numOcc
    //***************************************************************
    int numOcc[maxL+1][(int)(pow(2,12))]; //lengths[i][j] is number of occurences of a string of length i and decimal value j
    F0R(i, maxL+1) F0R(j, pow(2,12)) numOcc[i][j]=0;
    F0R(i, seqLength)
    {
        FOR(j, minLength, maxLength+1) if(i+j<=seqLength)
        {
            numOcc[j][toDec(sequence.substr(i,j))]++;
        }
    }
    //PRINTING OUT RESULTS (TOP N HIGHEST VALUES IN numOcc)
    //***************************************************************
    //using bucket sort to sort all the strings
    FOR(i, minLength, maxLength+1) F0R(j, pow(2,12))
    {
        buckets[numOcc[i][j]].push_back(toBase2(j,i));
    }
    int count = 0;
    FORd(i, minLength, seqLength+1)
    {
        if(buckets[i].size()>0)
        {
            count++;
            fout << i;
            sort(buckets[i].begin(),buckets[i].end(),compare);
            F0R(j, buckets[i].size())
            {
                if(j%6==0) fout << endl;
                else if(j!=0) fout << " ";
                fout << buckets[i].at(j);
            }
            fout << endl;
        }
        if(count==N) break;
    }
}

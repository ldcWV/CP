/*
 ID: ldorian1
 LANG: C++11
 TASK: shopping
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
#include <cstring>

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define INT_MAX 2147483647

using namespace std;

int numOffers, numProducts;
const int maxNumOffers = 99;
vector<pair<int, int>> offers[maxNumOffers];
int offerPrices[maxNumOffers];
int productPrices[5];
int quantities[5];
queue<int> offerInput;
vector<int> hashTable;
int dparr[6][6][6][6][6]; //dparr[a][b][c][d][e] is min price to buy a product 1's, b product 2's, etc ... e product 5's

int f(int a, int b, int c, int d, int e)
{
    if(a<0||b<0||c<0||d<0||e<0) return 10000000;
    if(dparr[a][b][c][d][e]!=-1) return dparr[a][b][c][d][e];
    int currMin = 10000000;
    F0R(i, numOffers) //test every offer
    {
        int a1 = a;
        int b1 = b;
        int c1 = c;
        int d1 = d;
        int e1 = e;
        F0R(j, offers[i].size())
        {
            int p = offers[i].at(j).first;
            if(p==0) a1-=offers[i].at(j).second;
            else if(p==1) b1-=offers[i].at(j).second;
            else if(p==2) c1-=offers[i].at(j).second;
            else if(p==3) d1-=offers[i].at(j).second;
            else if(p==4) e1-=offers[i].at(j).second;
        }
        if(f(a1,b1,c1,d1,e1)+offerPrices[i]<currMin) currMin=f(a1,b1,c1,d1,e1)+offerPrices[i];
    }
    F0R(i, numProducts) //test every product
    {
        int a1 = a;
        int b1 = b;
        int c1 = c;
        int d1 = d;
        int e1 = e;
        if(i==0) a1--;
        else if(i==1) b1--;
        else if(i==2) c1--;
        else if(i==3) d1--;
        else if(i==4) e1--;
        if(f(a1,b1,c1,d1,e1)+productPrices[i]<currMin) currMin=f(a1,b1,c1,d1,e1)+productPrices[i];
    }
    dparr[a][b][c][d][e]=currMin;
    return currMin;
}

int hashBack(vector<int> table, int b)
{
    F0R(i, table.size()) if(table.at(i)==b) return i;
    return -1;
}

int main()
{
    //READING INPUT
    ofstream fout("shopping.out");
    ifstream fin("shopping.in");
    fin >> numOffers;
    F0R(i, numOffers)
    {
        int t; fin >> t;
        offerInput.push(t);
        F0R(i, 2*t+1)
        {
            int t1; fin >> t1;
            offerInput.push(t1);
        }
    }
    fin >> numProducts;
    F0R(i, numProducts)
    {
        int code, q, price;
        fin >> code >> q >> price;
        hashTable.push_back(code);
        quantities[hashBack(hashTable,code)]=q;
        productPrices[hashBack(hashTable,code)]=price;
    }
    F0R(i, numOffers)
    {
        int numItems=offerInput.front(); offerInput.pop();
        F0R(j, numItems)
        {
            int c, k;
            c=offerInput.front(); offerInput.pop();
            k=offerInput.front(); offerInput.pop();
            offers[i].push_back({hashBack(hashTable,c),k});
        }
        offerPrices[i]=offerInput.front(); offerInput.pop();
    }
    
    //SETTING UP THE DP ARRAY
    F0R(a, 6) F0R(b, 6) F0R(c, 6) F0R(d, 6) F0R(e, 6) dparr[a][b][c][d][e]=-1;
    dparr[0][0][0][0][0]=0;
    fout << f(quantities[0], quantities[1], quantities[2], quantities[3], quantities[4]) << endl;
}

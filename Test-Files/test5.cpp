/*
 ID: ldorian1
 LANG: C++11
 TASK: test5
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

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

struct node {
    int value;
    int x;
    int y;
    node* left;
    node* right;
    node(int a, int b, int c) : value(a), x(b), y(c) {}
};

void update(int v, int pos, node* k) {
    k->value += v;
    if(k->x == k->y) return; //if it is a leaf
    int d = (k->x+k->y)/2;
    if(pos >= k->x && pos<=d) {
        if((k->left)->value==-1) {
            k->left = new node(0, k->x, d);
            (k->left)->left = new node(-1, -1, -1);
            (k->left)->right = new node(-1, -1, -1);
        }
        update(v, pos, k->left);
    }
    else {
        if((k->right)->value==-1) {
            k->right = new node(0, d+1, k->y);
            (k->right)->left = new node(-1, -1, -1);
            (k->right)->right = new node(-1, -1, -1);
        }
        update(v, pos, k->right);
    }
}

int sum(int a, int b, node* k) {
    if(b<k->x || a>k->y) return 0;
    if(k->x>=a && k->y<=b) return (k->value);
    int s = 0;
    if((k->left)->value != -1) s+=sum(a,b,k->left);
    if((k->right)->value != -1) s+=sum(a,b,k->right);
    return s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("test5.out");
    ifstream fin("test5.in");
    pi arr[5]; //first number of pair is the index, second number is the value
    arr[0]=make_pair(1, 5);
    arr[1]=make_pair(10, 15);
    arr[2]=make_pair(13, 33);
    arr[3]=make_pair(25, 2);
    arr[4]=make_pair(100, 14);
    
    node* root = new node(0, 0, 127);
    (root->left) = new node(-1, -1, -1);
    (root->right) = new node(-1, -1, -1);
    
    F0R(i, 5) {
        update(arr[i].S, arr[i].F, root);
    }
    cout << sum(2, 13, root) << endl;
    update(6, 3, root);
    cout << sum(2, 13, root) << endl;
}

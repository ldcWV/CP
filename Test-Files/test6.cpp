/*
 ID: ldorian1
 LANG: C++11
 TASK: test6
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

#define MAX_N 1000

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

int n, m;
int arr[MAX_N][MAX_N];
int bigSize = 1;
int smallSize = 1;

struct node {
    int value;
    int x, y;
    node* left;
    node* right;
    node(int v, int x, int y) : value(v), x(x), y(y) {}
};

struct treeNode {
    node* value;
    int x, y;
    treeNode* left;
    treeNode* right;
    treeNode(node* v, int x, int y) : value(v), x(x), y(y) {}
};

void updateSmall(int v, int y, node* k) {
    k->value+=v;
    if(k->x == k->y) return;
    int d = ((k->x)+(k->y))/2;
    if(y<=d) {
        if(!(k->left)) {
            k->left = new node(0, k->x, d);
            (k->left)->left = NULL;
            (k->left)->right = NULL;
        }
        updateSmall(v, y, k->left);
    }
    else {
        if(!(k->right)) {
            k->right = new node(0, d+1, k->y);
            (k->right)->left = NULL;
            (k->right)->right = NULL;
        }
        updateSmall(v, y, k->right);
    }
}

void update(int v, int x, int y, treeNode* k) {
    updateSmall(v, y, k->value);
    if(k->x == k->y) return;
    int d = ((k->x)+(k->y))/2;
    if(x<=d) {
        if(!(k->left)) {
            node* r = new node(0,0,smallSize);
            r->left = NULL;
            r->right = NULL;
            k->left = new treeNode(r, k->x, d);
            k->left->left=NULL;
            k->left->right=NULL;
        }
        update(v, x, y, k->left);
    }
    else {
        if(!(k->right)) {
            node* r = new node(0,0,smallSize);
            r->left = NULL;
            r->right = NULL;
            k->right = new treeNode(r, d+1, k->y);
            k->right->left=NULL;
            k->right->right=NULL;
        }
        update(v, x, y, k->right);
    }
}

int smallSum(int y1, int y2, node* k) {
    if(y2 < k->x || y1 > k->y) return 0;
    if(k->x >= y1 && k->y <= y2) return k->value;
    int s = 0;
    if(k->left) s+=smallSum(y1, y2, k->left);
    if(k->right) s+=smallSum(y1, y2, k->right);
    return s;
}

int sum(int x1, int x2, int y1, int y2, treeNode* k) {
    if(x2 < k->x || x1 > k->y) return 0;
    if(k->x >= x1 && k->y <= x2) return smallSum(y1, y2, k->value);
    int s = 0;
    if(k->left) s+=sum(x1, x2, y1, y2, k->left);
    if(k->right) s+=sum(x1, x2, y1, y2, k->right);
    return s;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ofstream fout("test6.out");
    ifstream fin("test6.in");
    fin >> n >> m;
    F0R(i, n) F0R(j, m) fin >> arr[i][j];
    while(bigSize<n) bigSize*=2;
    while(smallSize<m) smallSize*=2;
    bigSize--; smallSize--;
    
    node* rootRoot = new node(0, 0, smallSize);
    rootRoot->left = NULL;
    rootRoot->right = NULL;
    treeNode* bigRoot = new treeNode(rootRoot, 0, bigSize);
    bigRoot->left = NULL;
    bigRoot->right = NULL;
    F0R(i, n) F0R(j, m) update(arr[i][j], i, j, bigRoot);
    cout << sum(1, 2, 2, 3, bigRoot) << endl;
    update(3, 2, 2, bigRoot);
    cout << sum(1,2,2,3,bigRoot) << endl;
}

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
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define SQ(a) (a)*(a)

#define MOO(i, a, b) for (int i=a; i<b; i++)
#define M00(i, a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int,int> pi;

const ll MOD = 1000000007;

template<int SZ> struct matrix { //SZ should be max(N, M)
    ll mat[SZ][SZ];
    int N, M;
    matrix(int n, int m) { //identity
        this->N = n; this->M = m;
        M00(i, N) M00(j, M) {
            if(i == j) mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
    matrix operator*(const matrix& other) {
        if(M != other.N) throw "Dimensions don't match up";
        matrix<SZ> ans = matrix<SZ>(N, other.M);
        M00(i, N) M00(j, other.M) {
            ans.mat[i][j] = 0;
            M00(k, M) ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
        }
        return ans;
    }
    matrix operator+(const matrix& other) {
        if(N != other.N || M != other.M) throw "Dimensions don't match up";
        matrix<SZ> ans = matrix<SZ>(N, other.M);
        M00(i, N) M00(j, other.M) {
            ans.mat[i][j] = (mat[i][j] + other.mat[i][j]) % MOD;
        }
        return ans;
    }
    matrix operator^(ll p) {
        if(N != M) throw "Not a square matrix";
        matrix<SZ> ans = matrix<SZ>(N, N);
        matrix<SZ> temp = matrix<SZ>(N, M);
        M00(i, N) M00(j, M) temp.mat[i][j] = mat[i][j];
        while(p > 0) {
            if(p % 2) ans = ans*temp;
            temp = temp*temp;
            p /= 2;
        }
        return ans;
    }
    void print() {
        M00(i, N) {
            M00(j, M) {
                if(j != 0) cout << " ";
                cout << mat[i][j];
            }
            cout << "\n";
        }
    }
};

vector<vector<string>> lines;
unordered_map<string, int> variables;
int varcount = 0;
const int dim = 110;
int nested = 0;

bool isNumber(string s) {
    return isdigit(s[0]);
}

pair<matrix<dim>, int> processLoop(int ind, ll numIterations) { //also returns last line number
    matrix<dim> ans = matrix<dim>(varcount+1, varcount+1);
    ind++;
    while(lines[ind][0] != "}") {
        if(lines[ind][1] == "MOO") {
            auto t = processLoop(ind, stoi(lines[ind][0]));
            ans = t.F * ans;
            ind = t.S;
        } else {
            matrix<dim> mult = matrix<dim>(varcount+1, varcount+1);
            int v = variables[lines[ind][0]];
            mult.mat[v][v] = 0;
            MOO(i, 2, (int)lines[ind].size()) {
                if(lines[ind][i] != "(" && lines[ind][i] != ")" && lines[ind][i] != "+") {
                    if(isNumber(lines[ind][i])) mult.mat[v][varcount] = (mult.mat[v][varcount] + stoi(lines[ind][i])) % MOD;
                    else mult.mat[v][variables[lines[ind][i]]] = (mult.mat[v][variables[lines[ind][i]]] + 1) % MOD;
                }
            }
            ans = mult * ans;
        }
        ind++;
    }
    return MP(ans^numIterations, ind);
}

int main() { FAST
    ofstream fout("cowbasic.out");
    ifstream fin("cowbasic.in");
    string line;
    while(getline(fin, line)) {
        vector<string> s;
        string cur = "";
        M00(i, (int)line.length()) {
            if(line[i] == ' ') {
                if(cur != "") s.PB(cur);
                cur = "";
            } else {
                cur += line[i];
            }
        }
        if(cur != "") s.PB(cur);
        lines.PB(s);
    }
    M00(i, (int)(lines.size())) {
        if((int)lines[i].size() > 1 && lines[i][1] == "=") {
            if(!variables.count(lines[i][0])) {
                variables[lines[i][0]] = varcount++;
            }
        }
    }
    matrix<dim> res = matrix<dim>(varcount+1, varcount+1);
    M00(i, (int)(lines.size()-1)) {
        if(lines[i][1] == "MOO") {
            auto t = processLoop(i, stoi(lines[i][0]));
            res = t.F * res;
            i = t.S;
        } else {
            matrix<dim> mult = matrix<dim>(varcount+1, varcount+1);
            int v = variables[lines[i][0]];
            mult.mat[v][v] = 0;
            MOO(j, 2, (int)lines[i].size()) {
                if(lines[i][j] != "(" && lines[i][j] != ")" && lines[i][j] != "+") {
                    if(isNumber(lines[i][j])) mult.mat[v][varcount] = (mult.mat[v][varcount]+stoi(lines[i][j])) % MOD;
                    else mult.mat[v][variables[lines[i][j]]] = (mult.mat[v][variables[lines[i][j]]]+1) % MOD;
                }
            }
            res = mult * res;
        }
    }
    string vres = lines[(int)lines.size()-1][1];
    int ind = variables[vres];
    ll ans = 0;
    M00(i, varcount+1) ans = (ans + res.mat[ind][i]) % MOD;
    fout << ans << "\n";
}

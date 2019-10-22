/**
* Description: ?
* Time: O(N\log N)
* Source: SuprDewd, KACTL, majk, ekzhang
* Verification: 
	* http://usaco.org/index.php?page=viewproblem2&cpid=768
		* https://pastebin.com/y2Z9FYr6
	* https://open.kattis.com/problems/suffixsorting
	* https://codeforces.com/contest/1090/problem/J
*/

template<int SZ> struct suffixArray {
    const static int LGSZ = 33-__builtin_clz(SZ-1);
    pair<pi, int> tup[SZ];
    int sortIndex[LGSZ][SZ];
    int res[SZ];
    int len;
    suffixArray(string s) {
        this->len = (int)s.length();
        M00(i, len) tup[i] = MP(MP((int)s[i], -1), i);
        sort(tup, tup+len);
        int temp = 0;
        tup[0].F.F = 0;
        MOO(i, 1, len) {
            if(s[tup[i].S] != s[tup[i-1].S]) temp++;
            tup[i].F.F = temp;
        }
        M00(i, len) sortIndex[0][tup[i].S] = tup[i].F.F;
        MOO(i, 1, LGSZ) {
            M00(j, len) tup[j] = MP(MP(sortIndex[i-1][j], (j+(1<<(i-1))<len)?sortIndex[i-1][j+(1<<(i-1))]:-1), j);
            sort(tup, tup+len);
            int temp2 = 0;
            sortIndex[i][tup[0].S] = 0;
            MOO(j, 1, len) {
                if(tup[j-1].F != tup[j].F) temp2++;
                sortIndex[i][tup[j].S] = temp2;
            }
        }
        M00(i, len) res[sortIndex[LGSZ-1][i]] = i;
    }
    int LCP(int x, int y) {
        if(x == y) return len - x;
        int ans = 0;
        M00d(i, LGSZ) {
            if(x >= len || y >= len) break;
            if(sortIndex[i][x] == sortIndex[i][y]) {
                x += (1<<i);
                y += (1<<i);
                ans += (1<<i);
            }
        }
        return ans;
    }
};

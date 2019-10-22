/**
 * Source: WhaleVomit
 * Time: O(N)\text{ build, }O(1)\text{ get hash value of a substring}
 * Description: generates hash values of any substring in $O(1)$, equal strings have same hash value
 * Verification: lmao imagine verifying
 */

template<int SZ> struct rabinKarp {
    const ll mods[3] = {1000000007, 999119999, 1000992299};
    ll p[3][SZ];
    ll h[3][SZ];
    const ll base = 1000696969;
    rabinKarp() {}
    void build(string a) {
        M00(i, 3) {
            p[i][0] = 1;
            h[i][0] = (int)a[0];
            MOO(j, 1, (int)a.length()) {
                p[i][j] = (p[i][j-1] * mods[i]) % base;
                h[i][j] = (h[i][j-1] * mods[i] + (int)a[j]) % base;
            }
        }
    }
    tuple<ll, ll, ll> hsh(int a, int b) {
        if(a == 0) return make_tuple(h[0][b], h[1][b], h[2][b]);
        tuple<ll, ll, ll> ans;
        get<0>(ans) = (((h[0][b] - h[0][a-1]*p[0][b-a+1]) % base) + base) % base;
        get<1>(ans) = (((h[1][b] - h[1][a-1]*p[1][b-a+1]) % base) + base) % base;
        get<2>(ans) = (((h[2][b] - h[2][a-1]*p[2][b-a+1]) % base) + base) % base;
        return ans;
    }
};

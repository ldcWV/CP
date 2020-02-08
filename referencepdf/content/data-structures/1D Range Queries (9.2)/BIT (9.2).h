/**
 * Description: binary indexed tree
 * Source: https://codeforces.com/blog/entry/64914
 * Verification: SPOJ matsum
 * Time: O(\log N)
 */

template<int sz> struct BIT {
    int b[sz+1];
    BIT() {
        M00(i, sz+1) b[i] = 0;
    }
    void add(int k, int val) {
        k++;
        for(; k <= sz; k+=(k&-k)) b[k] += val;
    }
    int psum(int ind) {
        int ans = 0;
        ind++;
        for(; ind>0; ind-=(ind&-ind)) ans+=b[ind];
        return ans;
    }
    int sum(int l, int r) {
        return psum(r) - psum(l-1);
    }
};

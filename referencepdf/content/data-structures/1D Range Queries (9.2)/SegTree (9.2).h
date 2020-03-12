/**
 * Description: 1D point update, range query
 * Time: O(\log N)
 * Source: 
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 */

template<class T, int SZ> struct segtree {
    // modify these
    T identity = 0;
    T comb(T l, T r) {
        return l + r;
    }
    void updLeaf(T& l, T val) {
        l = val;
    }
    
    T tree[2*SZ+1];
    segtree() {
        M00(i, 2*SZ+1) tree[i] = identity;
    }
    void upd(int pos, T val) {
        pos += SZ+1;
        updLeaf(tree[pos], val);
        for(pos >>= 1; pos >= 1; pos >>= 1) {
            tree[pos] = comb(tree[2*pos], tree[2*pos+1]);
        }
    }
    T query(int l, int r) {
        l += SZ+1;
        r += SZ+1;
        T res = identity;
        while(l <= r) {
            if(l&1) res = comb(res, tree[l++]);
            if(!(r&1)) res = comb(res, tree[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

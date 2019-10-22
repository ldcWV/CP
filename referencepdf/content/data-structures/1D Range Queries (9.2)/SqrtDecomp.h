/**
 * Description: 1D point update, range query
 * Time: O(\sqrt{N})
 * Source: imagine
 * Verification: imagine
 */

struct sqrtDecomp {
    const static int blockSZ = 10; //change this
    int val[blockSZ*blockSZ];
    int lazy[blockSZ];
    
    sqrtDecomp() {
        M00(i, blockSZ*blockSZ) val[i] = 0;
        M00(i, blockSZ) lazy[i] = 0;
    }
    void upd(int l, int r, int v) {
        int ind = l;
        while(ind%blockSZ && ind <= r) {
            val[ind] += v;
            lazy[ind/blockSZ] += v;
            ind++;
        }
        while(ind + blockSZ <= r) {
            lazy[ind/blockSZ] += v*blockSZ;
            ind += blockSZ;
        }
        while(ind <= r) {
            val[ind] += v;
            lazy[ind/blockSZ] += v;
            ind++;
        }
    }
    int query(int l, int r) {
        int res = 0;
        int ind = l;
        while(ind%blockSZ && ind <= r) {
            res += val[ind];
            ind++;
        }
        while(ind + blockSZ <= r) {
            res += lazy[ind/blockSZ];
            ind += blockSZ;
        }
        while(ind <= r) {
            res += val[ind];
            ind++;
        }
        return res;
    }
};

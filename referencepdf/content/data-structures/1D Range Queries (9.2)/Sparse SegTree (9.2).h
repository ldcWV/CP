/**
 * Description: Does not allocate storage for nodes with no data
 * Source: USACO Mowing the Field
 * Verification: ~
 */ 

template<class T> struct node {
    T val;
    int l, r;
    node* left;
    node* right;
    node(int l, int r) {
        this -> l = l;
        this -> r = r;
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

template<class T, int SZ> struct segtree {
    // modify these
    T identity = 0;
    T comb(T l, T r) {
        return l + r;
    }
    void updLeaf(T& l, T val) {
        l = val;
    }
    
    node<T>* root;
    segtree() {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node<T>(0, ub-1);
        root->val = identity;
    }
    void updN(node<T>* n, int pos, T val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            updLeaf(n->val, val);
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) {
                n->right = new node<T>(mid+1, n->r);
                n->right->val = identity;
            }
            updN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) {
                n->left = new node<T>(n->l, mid);
                n->left->val = identity;
            }
            updN(n->left, pos, val);
        }
        
        T lv = (n->left == nullptr) ? identity : n->left->val;
        T rv = (n->right == nullptr) ? identity : n->right->val;
        n->val = comb(lv, rv);
    }
    void upd(int pos, T val) {
        updN(root, pos, val);
    }
    T queryN(node<T>* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return identity;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        T a = identity;
        if(n->left != nullptr) a = comb(a, queryN(n->left, i1, i2));
        if(n->right != nullptr) a = comb(a, queryN(n->right, i1, i2));
        
        return a;
    }
    T query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

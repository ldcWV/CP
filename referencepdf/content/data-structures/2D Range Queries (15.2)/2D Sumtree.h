/**
 * Description: Lawrence's 2d sum segment tree
 * Source: ?
 * Verification: ?
 */

struct sumtreenode{
    node* root;
    sumtreenode* left;
    sumtreenode* right;
    int l, r;
    sumtreenode(int l, int r, int SZ) {
        int ub = 1;
        while(ub < SZ) ub *= 2;
        root = new node(0, ub-1);
        this -> l = l;
        this -> r = r;
        this->left = nullptr;
        this->right = nullptr;
    }
    void updN(node* n, int pos, int val) {
        if(pos < n->l || pos > n->r) return;
        if(n->l == n->r) {
            n->val = val;
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(pos > mid) {
            if(n->right == nullptr) n->right = new node(mid+1, n->r);
            updN(n->right, pos, val);
        }
        else {
            if(n->left == nullptr) n->left = new node(n->l, mid);
            updN(n->left, pos, val);
        }
        
        int s = 0;
        if(n->right != nullptr) s += n->right->val;
        if(n->left != nullptr) s += n->left->val;
        n->val = s;
    }
    void upd(int pos, int val) {
        updN(root, pos, val);
    }
    int queryN(node* n, int i1, int i2) {
        if(i2 < n->l || i1 > n->r) return 0;
        if(n->l == n->r) return n->val;
        if(n->l >= i1 && n->r <= i2) return n->val;
        
        int s = 0;
        if(n->left != nullptr) s += queryN(n->left, i1, i2);
        if(n->right != nullptr) s += queryN(n->right, i1, i2);
        
        return s;
    }
    int query(int i1, int i2) {
        return queryN(root, i1, i2);
    }
};

template<int w, int h> struct sumtree2d{
    sumtreenode* root;
    sumtree2d() {
        int ub = 1;
        while(ub < w) ub *= 2;
        this->root = new sumtreenode(0, ub-1, h);
        root->left = nullptr;
        root->right = nullptr;
    }
    void updN(sumtreenode* n, int x, int y, int val) {
        if(x < n->l || x > n->r) return;
        if(n->l == n->r) {
            n->upd(y, val);
            return;
        }
        
        int mid = (n->l + n->r)/2;
        if(x > mid) {
            if(n->right == nullptr) n->right = new sumtreenode(mid+1, n->r, h);
            updN(n->right, x, y, val);
        }
        else {
            if(n->left == nullptr) n->left = new sumtreenode(n->l, mid, h);
            updN(n->left, x, y, val);
        }
        
        int s = 0;
        if(n->left != nullptr) s += n->left->query(y, y);
        if(n->right != nullptr) s += n->right->query(y, y);
        n->upd(y, s);
    }
    void upd(int x, int y, int val) {
        updN(root, x, y, val);
    }
    int queryN(sumtreenode* n, int x1, int y1, int x2, int y2) {
        if(x2 < n->l || x1 > n->r) return 0;
        if(n->l == n->r) return n->query(y1, y2);
        if(n->l >= x1 && n->r <= x2) return n->query(y1, y2);
        
        int s = 0;
        if(n->left != nullptr) s += queryN(n->left, x1, y1, x2, y2);
        if(n->right != nullptr) s += queryN(n->right, x1, y1, x2, y2);
        
        return s;
    }
    int query(int x1, int y1, int x2, int y2) {
        return queryN(root, x1, y1, x2, y2);
    }
};

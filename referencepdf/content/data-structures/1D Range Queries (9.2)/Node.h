/**
 * Description: Node
 * Source: ?
 * Verification: ?
 */

struct node {
    int val;
    int lazy;
    int l, r;
    node* left;
    node* right;
    node(int l, int r) {
        this -> val = 0;
        this -> lazy = 0;
        this -> l = l;
        this -> r = r;
        this -> left = nullptr;
        this -> right = nullptr;
    }
};

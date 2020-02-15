/**
 * Description: trie
 * Source: CF Algorithms Gym
 * Verification: January Easy 2018 - Shubham and Subarray Xor
 */

struct tnode {
    char c;
    bool used;
    tnode* next[26];
    tnode() {
        c = ' ';
        used = 0;
        M00(i, 26) next[i] = nullptr;
    }
};

tnode* root;

void addToTrie(string s) {
    tnode* cur = root;
    for(char ch: s) {
        int idx = ch - 'a';
        if(cur->next[idx] == nullptr) {
            cur->next[idx] = new tnode();
        }
        cur = cur->next[idx];
        cur->c = ch;
    }
    cur->used = 1;
}

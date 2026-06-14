#include <bits/stdc++.h>
using namespace std;

#define Order 5 // NOTE: Maximum number of childrens
// TODO: Make the order dynamic at some point.

class TreeNode {
  public:
    int keyCount;
    int *keys;
    TreeNode **childrens;

    TreeNode() {
        keyCount = 0;
        keys = new int[Order - 1];
        childrens = new TreeNode *[Order];
    }

    // Lower Bound
    int search(int val) {
        int l = 0, r = keyCount;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (keys[m] >= val)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};

class BTree {
    TreeNode *root;
    uint size;

  public:
    BTree() : root(nullptr), size(0) {}

    bool search(int val) {
        if (size == 0)
            return false;
        TreeNode *curr = root;
        while (curr) {
            int i = curr->search(val);

            if (i < curr->keyCount && curr->keys[i] == val)
                return true;
            else
                curr = curr->childrens[i];
        }
        return false;
    }
    // TODO:
    void insert(int val) {}
    void remove(int val) {}
};

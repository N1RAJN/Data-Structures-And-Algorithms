#include <bits/stdc++.h>
using namespace std;

class TreeNode {
    friend class BTree;
    static int order; // NOTE: Maximum number of childrens
    bool isLeaf;
    int keyCount;
    int *keys;
    TreeNode **childrens;

    static int maxKeys() { return order - 1; }
    static int minKeys() { return (order + 1) / 2 - 1; }

  public:
    TreeNode(int _order, bool _isLeaf) : isLeaf(_isLeaf), keyCount(0) {
        keys = new int[maxKeys()];
        childrens = new TreeNode *[_order];
    }
    int search(int val);
    void insertNonFull(int val);
    void splitChild(int childIndex, TreeNode *child);
};

class BTree {
    TreeNode *root;
    int order;
    uint size;

  public:
    BTree(int _order) : root(nullptr), size(0), order(_order) {
        TreeNode::order = _order;
    }
    bool search(int val);
    void insert(int val);
    void remove(int val);
};

int TreeNode::search(int val) {
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

void TreeNode::insertNonFull(int val) {
    // NOTE: If leaf node, insert in the right place
    if (isLeaf) {
        int index = keyCount - 1;
        while (index >= 0 && val < keys[index]) {
            keys[index + 1] = keys[index];
            index--;
        }
        keys[index + 1] = val;
        keyCount++;
    } else {
        // NOTE: If internal node, find the correct child to recursively
        // insert to, while splitting the child if max keyCount
        int index = search(val);

        if (childrens[index]->keyCount == maxKeys()) {
            splitChild(index, childrens[index]);

            if (keys[index] < val)
                index++;
        }
        childrens[index]->insertNonFull(val);
    }
}

void TreeNode::splitChild(int childIndex, TreeNode *child) {
    TreeNode *newChild = new TreeNode(TreeNode::order, child->isLeaf);
    int mid = child->keyCount / 2;
    int promoteKey = child->keys[mid];
    newChild->keyCount = child->keyCount - mid - 1;

    // NOTE: Copy right half of child into newChild
    for (int i = 0; i < newChild->keyCount; ++i)
        newChild->keys[i] = child->keys[i + mid + 1];

    // NOTE: If child was an internal node, copy the pointers to its
    // children
    if (!child->isLeaf)
        for (int i = 0; i <= newChild->keyCount; ++i)
            newChild->childrens[i] = child->childrens[i + mid + 1];

    child->keyCount = mid;

    // NOTE: Insert the pointer to newChild in the right place.
    for (int i = this->keyCount; i >= childIndex; --i)
        this->childrens[i + 1] = this->childrens[i];
    this->childrens[childIndex + 1] = newChild;

    // NOTE: Promote the median key of child to the parent node.
    for (int i = this->keyCount - 1; i >= childIndex; --i)
        this->keys[i + 1] = this->keys[i];
    this->keys[childIndex] = child->keys[mid];
    this->keyCount++;
}

bool BTree::search(int val) {
    if (size == 0)
        return false;
    TreeNode *curr = root;
    while (curr) {
        int i = curr->search(val);

        if (i < curr->keyCount && curr->keys[i] == val)
            return true;
        if (curr->isLeaf)
            return false;
        curr = curr->childrens[i];
    }
    return false;
}
void BTree::insert(int val) {
    if (root == nullptr) {
        root = new TreeNode(order, true);
        root->keys[0] = val;
        root->keyCount++;
    } else {
        if (root->keyCount == root->maxKeys()) {
            TreeNode *newRoot = new TreeNode(order, false);

            newRoot->childrens[0] = root;
            newRoot->splitChild(0, root);

            newRoot->insertNonFull(val);

            root = newRoot;
        } else {
            root->insertNonFull(val);
        }
    }
}
void BTree::remove(int val) {}

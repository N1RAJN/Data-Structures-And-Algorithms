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
    static int minKeys() { return order / 2 - 1; }

  public:
    TreeNode(int _order, bool _isLeaf) : isLeaf(_isLeaf), keyCount(0) {
        keys = new int[maxKeys()];
        childrens = new TreeNode *[_order];
    }
    int search(int val);
    void insertNonFull(int val);
    void splitChild(int childIndex, TreeNode *child);
    int getPredecessor(int index);
    int getSuccessor(int index);
    void merge(int index);
    void removeFromLeaf(int index);
    void removeFromNonLeaf(int index);
    void borrowFromPrev(int index);
    void borrowFromNext(int index);
    void fill(int index);
    void deletion(int val);
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

// NOTE: Lower bound i.e, first keys[l] >= val, which means if the val exists in
// the tree, it would be in lth index or the lth children node
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
        // insert to, while pre-emptively splitting the child if max keyCount
        int index = TreeNode::search(val);

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
    // ("this" is implicit but explicitly writing it makes it clearer which node
    // is being worked with i.e, the parent)
    for (int i = this->keyCount; i >= childIndex; --i)
        this->childrens[i + 1] = this->childrens[i];
    this->childrens[childIndex + 1] = newChild;

    // NOTE: Promote the median key of child to the parent node.
    for (int i = this->keyCount - 1; i >= childIndex; --i)
        this->keys[i + 1] = this->keys[i];
    this->keys[childIndex] = child->keys[mid];
    this->keyCount++;
}

int TreeNode::getPredecessor(int index) {
    TreeNode *curr = childrens[index];
    while (!curr->isLeaf)
        curr = curr->childrens[curr->keyCount];
    return curr->keys[curr->keyCount - 1];
}

int TreeNode::getSuccessor(int index) {
    TreeNode *curr = childrens[index + 1];
    while (!curr->isLeaf)
        curr = curr->childrens[0];
    return curr->keys[0];
}

void TreeNode::removeFromLeaf(int index) {
    for (int i = index + 1; i < keyCount; ++i) {
        keys[i - 1] = keys[i];
    }
    keyCount--;
}

void TreeNode::removeFromNonLeaf(int index) {
    int val = keys[index];

    // NOTE: Replace the val to be deleted with either its inorder predecessor
    // or successor, and delete the pred/succ. If both left and right sibling
    // node have less than minKeys, merge them and delete the val;
    if (childrens[index]->keyCount > minKeys()) {
        int pred = getPredecessor(index);
        keys[index] = pred;
        childrens[index]->deletion(pred);
    } else if (childrens[index + 1]->keyCount > minKeys()) {
        int succ = getSuccessor(index);
        keys[index] = succ;
        childrens[index]->deletion(succ);
    } else {
        TreeNode::merge(index);
        childrens[index]->deletion(val);
    }
}

void TreeNode::borrowFromPrev(int index) {
    // NOTE: keys[index] -> key separating child and left sibling
    TreeNode *child = childrens[index];
    TreeNode *sibling = childrens[index - 1];

    // Shift keys (and children) of child
    for (int i = child->keyCount - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->isLeaf) {
        for (int i = child->keyCount; i >= 0; --i)
            child->childrens[i + 1] = child->childrens[i];
    }

    // Borrow from parent
    child->keys[0] = this->keys[index - 1];
    if (!sibling->isLeaf)
        child->childrens[0] = sibling->childrens[sibling->keyCount];

    // Promote last key of sibling to parent
    this->keys[index - 1] = sibling->keys[sibling->keyCount - 1];

    child->keyCount++;
    sibling->keyCount--;
}

void TreeNode::borrowFromNext(int index) {
    TreeNode *child = childrens[index];
    TreeNode *sibling = childrens[index + 1];

    // Shift keys (and children) of sibling
    for (int i = 0; i < sibling->keyCount; ++i)
        sibling->keys[i] = sibling->keys[i + 1];

    if (!sibling->isLeaf) {
        for (int i = 0; i <= sibling->keyCount; ++i)
            sibling->childrens[i + 1] = sibling->childrens[i];
    }

    // Borrow from parent
    int n = child->keyCount;
    child->keys[n] = this->keys[index];
    if (!sibling->isLeaf)
        child->childrens[n + 1] = sibling->childrens[0];

    // Promote last key of sibling to parent
    this->keys[index] = sibling->keys[0];

    child->keyCount++;
    sibling->keyCount--;
}

void TreeNode::merge(int index) {
    TreeNode *child = childrens[index];
    TreeNode *sibling = childrens[index + 1];

    int lastSlot = child->keyCount;

    // Demote the separater key of parent
    child->keys[lastSlot++] = keys[index];

    for (int i = index + 1; i < keyCount; ++i)
        keys[i - 1] = keys[i];

    for (int i = index + 2; i <= keyCount; ++i)
        childrens[i - 1] = childrens[i];

    // Copy keys (and children) from the sibling
    for (int i = 0; i < sibling->keyCount; ++i)
        child->keys[lastSlot + i] = sibling->keys[i];

    if (!sibling->isLeaf) {
        for (int i = 0; i <= sibling->keyCount; ++i)
            child->childrens[lastSlot + i] = sibling->childrens[i];
    }

    child->keyCount += sibling->keyCount + 1;
    keyCount--;
}

void TreeNode::fill(int index) {
    if (index != 0 && childrens[index - 1]->keyCount > minKeys())
        borrowFromPrev(index);
    else if (index != keyCount && childrens[index + 1]->keyCount > minKeys())
        borrowFromNext(index);
    else {
        if (index == keyCount)
            merge(index - 1);
        else
            merge(index);
    }
}

void TreeNode::deletion(int val) {
    int idx = TreeNode::search(val);
    if (idx < keyCount && keys[idx] == val) {
        if (isLeaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (isLeaf) {
            cout << val << " doesn't exist in the tree\n";
            return;
        }

        // NOTE: val is potentially in the last children node
        bool isLastIdx = idx == keyCount ? true : false;

        // NOTE: Preemptive fill
        if (childrens[idx]->keyCount < minKeys())
            TreeNode::fill(idx);

        // NOTE: Recursion target node was the last children and it got
        // merged to the previous one
        if (isLastIdx && idx > keyCount)
            childrens[idx - 1]->deletion(val);
        else
            childrens[idx]->deletion(val);
    }
}

bool BTree::search(int val) {
    if (size == 0)
        return false;
    TreeNode *curr = root;
    while (curr) {
        int i = curr->TreeNode::search(val);

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
void BTree::remove(int val) {
    if (!root) {
        cout << "Empty Tree\n";
        return;
    }
    root->deletion(val);

    if (root->keyCount == 0) {
        TreeNode *temp = root;

        // NOTE: If root has 0 keys, then it'd have to have 1 children
        if (!root->isLeaf)
            root = root->childrens[0];
        else
            root = nullptr;

        delete temp;
    }
}

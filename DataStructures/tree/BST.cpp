#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {};
    TreeNode(int _val, TreeNode *l) : val(_val), left(l), right(nullptr) {};
    TreeNode(int _val, TreeNode *l, TreeNode *r)
        : val(_val), left(l), right(r) {};
};

class BinarySearchTree {
    TreeNode *root;
    unsigned int size;

    TreeNode *getSuccessor(TreeNode *subtreeRoot) {
        if (!subtreeRoot)
            return subtreeRoot;
        while (subtreeRoot && subtreeRoot->left)
            subtreeRoot = subtreeRoot->left;
        return subtreeRoot;
    }

    TreeNode *removeNode(TreeNode *node, int val) {
        if (!node)
            return node;
        if (node->val > val) {
            node->left = removeNode(node->left, val);
        } else if (node->val < val) {
            node->right = removeNode(node->right, val);
        } else {
            // Handles both 0 children and only right children
            if (!node->left) {
                TreeNode *temp = node->right;
                delete node;
                size--;
                return temp;
            }
            // Only left children
            if (!node->right) {
                TreeNode *temp = node->left;
                delete node;
                size--;
                return temp;
            }

            // Two children
            TreeNode *succesor = getSuccessor(node->right);
            node->val = succesor->val;
            node->right = removeNode(node->right, succesor->val);
        }
        return node;
    }

  public:
    BinarySearchTree() : root(nullptr), size(0) {};
    BinarySearchTree(int _val) : size(1) { root = new TreeNode(_val); };

    bool search(int val) {
        if (isEmpty())
            return false;
        TreeNode *curr = root;
        while (curr) {
            int currVal = curr->val;
            if (currVal == val)
                return true;
            else if (currVal > val)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return false;
    }
    void insert(int val) {
        if (!root) {
            root = new TreeNode(val);
            size++;
            return;
        }
        TreeNode *curr = root;
        while (curr) {
            int currVal = curr->val;
            if (currVal == val) {
                cout << "Duplicate Values not allowed\n";
                return;

            } else if (currVal > val) {
                if (curr->left)
                    curr = curr->left;
                else {
                    curr->left = new TreeNode(val);
                    size++;
                    return;
                }
            } else {
                if (curr->right)
                    curr = curr->right;
                else {
                    curr->right = new TreeNode(val);
                    size++;
                    return;
                }
            }
        }
    }
    void remove(int val) {
        if (!root) {
            cout << "Empty Tree\n";
            return;
        }
        root = removeNode(root, val);
    }

    unsigned int getSize() { return size; }
    bool isEmpty() { return size == 0; }
};

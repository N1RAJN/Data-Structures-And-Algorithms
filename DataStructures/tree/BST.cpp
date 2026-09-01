#include <bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    Node *left;
    Node *right;

    Node() : val(0), left(nullptr), right(nullptr) {};
    Node(int _val) : val(_val), left(nullptr), right(nullptr) {};
    Node(int _val, Node *l) : val(_val), left(l), right(nullptr) {};
    Node(int _val, Node *l, Node *r) : val(_val), left(l), right(r) {};
};

class BST {
    Node *root;
    unsigned int size;

    Node *getSuccessor(Node *node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node *_remove(Node *node, int val) {
        if (!node)
            return node;
        if (node->val > val) {
            node->left = _remove(node->left, val);
        } else if (node->val < val) {
            node->right = _remove(node->right, val);
        } else {
            // Handles both 0 children and only right children
            if (!node->left) {
                Node *temp = node->right;
                delete node;
                size--;
                return temp;
            }
            // Only left children
            if (!node->right) {
                Node *temp = node->left;
                delete node;
                size--;
                return temp;
            }

            // Two children
            Node *succesor = getSuccessor(node->right);
            node->val = succesor->val;
            node->right = _remove(node->right, succesor->val);
        }
        return node;
    }

  public:
    BST() : root(nullptr), size(0) {};
    BST(int _val) : size(1) { root = new Node(_val); };

    bool search(int val) {
        if (isEmpty())
            return false;
        Node *curr = root;
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
            root = new Node(val);
            size++;
            return;
        }

        Node *curr = root;
        while (curr) {
            int currVal = curr->val;
            if (currVal == val) {
                cout << "Duplicate Values not allowed\n";
                return;
            } else if (val < currVal) {
                if (curr->left)
                    curr = curr->left;
                else {
                    curr->left = new Node(val);
                    size++;
                    return;
                }
            } else {
                if (curr->right)
                    curr = curr->right;
                else {
                    curr->right = new Node(val);
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
        root = _remove(root, val);
    }

    unsigned int getSize() { return size; }

    bool isEmpty() { return size == 0; }
};

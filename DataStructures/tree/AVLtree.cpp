#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    int height;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), height(1), left(nullptr), right(nullptr) {};
    TreeNode(int _val) : val(_val), height(1), left(nullptr), right(nullptr) {};
};

class AVLtree {
    TreeNode *root;
    size_t size;

    size_t getHeight(TreeNode *node) {
        if (!node)
            return 0;
        return node->height;
    }

    int balanceFactor(TreeNode *node) {
        if (!node)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // NOTE: When removing a node with 2 children from a BST, it can replaced
    // (while preserving the BST property) by its
    // a. inorder-predecessor (value just before the node in inorder traversal),
    // which is the largest value in the left subtree or
    // b. inorder-successor (value just after the node in inorder traversal),
    // which is the smallest value in the right subtree
    TreeNode *getSuccessor(TreeNode *subTree) {
        if (!subTree)
            return subTree;
        TreeNode *curr = subTree;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }
    /* NOTE:
     * Left-Rotation                Right-Rotation
     *  4                                6
     *   \                 5            /
     *    5         ->    / \    <-    5
     *     \             4   6        /
     *      6                        4
     */

    // NOTE: For left-left case
    // Think of the middle node (child) as the pivot, and you applied gravity
    // The parent node falls in RIGHT direction (hence right rotation)
    TreeNode *rightRotate(TreeNode *parent) {
        TreeNode *child = parent->left;
        TreeNode *rightGrandChild = child->right;

        child->right = parent;          // NOTE: think of it as the falling part
        parent->left = rightGrandChild; // NOTE: this is connecting the severed
                                        // link (child->right, parent->left)

        // NOTE: Update the parent's height first, because it's now lower in the
        // tree
        parent->height =
            1 + max(getHeight(parent->left), getHeight(parent->right));
        child->height =
            1 + max(getHeight(child->left), getHeight(child->right));

        return child;
    }

    // NOTE: For right-right case
    // Same as above but it falls in the left direction
    TreeNode *leftRotate(TreeNode *parent) {
        TreeNode *child = parent->right;
        TreeNode *leftGrandChild = child->left;

        child->left = parent;
        parent->right = leftGrandChild;

        parent->height =
            1 + max(getHeight(parent->left), getHeight(parent->right));
        child->height =
            1 + max(getHeight(child->left), getHeight(child->right));

        return child;
    }

    // NOTE: 1. Insert the node as in a normal BST
    // 2. Update the heights of the added node
    // 3. Check the balance factor of the node
    // 4. If not AVL (balance factor outside the range [-1,1])
    // find the correct case out of 4, and rotate accord.
    // 5. If AVL, Return the node
    TreeNode *insertNode(TreeNode *node, int val) {
        // NOTE: 1. normal insertion
        if (!node) {
            size++;
            return new TreeNode(val);
        }
        if (val == node->val) {
            return node;
        } else if (val < node->val) {
            node->left = insertNode(node->left, val);
        } else {
            node->right = insertNode(node->right, val);
        }
        // NOTE: 2. Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // NOTE: 3. Check AVL and rotate if necessary
        int balance = balanceFactor(node);

        // NOTE: 4 cases, out of which 2 are the main
        // i.e, left-left (right rotate) and right-right (left rotate)
        // For left-right, get it to left-left (left-rotate child)
        // For right-left, get it to right-right (right rotate child)

        // NOTE: Way to think about the cases
        // Just a way of (sequentially) representing the links
        // Eg. left-left = parent->left->left;

        // Left-Left
        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        // Left-Right
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right-Right
        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        // Right-Left
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        // NOTE: Cause already AVL
        return node;
    }

    // NOTE: Same as insertion:
    // 1. Normal removal as BST
    // 2. Update balance factor
    // 3. Check for imbalance
    // 4. Rotate if needed
    TreeNode *removeNode(TreeNode *node, int val) {
        // NOTE: 1. Removal
        if (!node)
            return node;
        if (val < node->val) {
            node->left = removeNode(node->left, val);
        } else if (val > node->val) {
            node->right = removeNode(node->right, val);
        } else {
            // NOTE: The two if statements handle each cases for node with 1
            // children
            // The first one (more like any one of them, but whichever is first)
            // also handles node with zero children
            if (node->left == nullptr) {
                TreeNode *temp = node->right;
                delete node;
                size--;
                return temp;
            }
            if (node->right == nullptr) {
                TreeNode *temp = node->left;
                delete node;
                size--;
                return temp;
            }

            // NOTE: Node with 2 children
            // Replace it with in-order successor
            TreeNode *successor = getSuccessor(node->right);
            node->val = successor->val;
            node->right = removeNode(node->right, successor->val);
        }
        // NOTE: 2. Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // NOTE: 3. Check for imbalance and rotate if necessary
        int balance = balanceFactor(node);

        // Left-Left
        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        // Left-Right
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right-Right
        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        // Right-Left
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

  public:
    AVLtree() : root(nullptr), size(0) {};
    AVLtree(int _val) : root(new TreeNode(_val)), size(1) {};

    void insert(int val) { root = insertNode(root, val); }
    void remove(int val) { root = removeNode(root, val); }
};

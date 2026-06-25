#include <bits/stdc++.h>
using namespace std;

enum COLOR { RED, BLACK };
struct TreeNode {
    COLOR color;
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : color(BLACK), val(0) {}
    TreeNode(int _val) : color(RED), val(_val) {};
};

// NOTE:
// 1. Each node is either red or black
// 2. All 'nil' nodes are black
// 3. Red nodes can't have red parent/childrens. (can't be adjacent)
// 4. For any node (not including the node itself), a simple path from the node
// to any 'nil' node must have the same number of black nodes.
class RBTree {
    TreeNode *root;
    int size;
    TreeNode *nil;
    TreeNode *createNewNode(int val) {
        TreeNode *node = new TreeNode(val);
        node->left = node->right = node->parent = nil;
        return node;
    }

    void leftRotate(TreeNode *parent);
    void rightRotate(TreeNode *parent);
    TreeNode *getSuccessor(TreeNode *node);
    void transplant(TreeNode *target, TreeNode *source);
    TreeNode *getNode(int val);
    void fixInsertion(TreeNode *node);
    void fixDeletion(TreeNode *node);

  public:
    RBTree() : size(0) {
        nil = new TreeNode();
        nil->parent = nil->left = nil->right = nil;
        root = nil;
    }
    void insert(int val);
    bool search(int val);
    void remove(int val);
};

// NOTE: Same as AVL rotations with extra parent links and checking for nil
// nodes
void RBTree::leftRotate(TreeNode *node) {
    TreeNode *grandParent = node->parent;
    TreeNode *child = node->right;
    TreeNode *leftGrandChild = child->left;

    child->left = node;
    node->parent = child;

    // Promote child to be node
    child->parent = grandParent;
    if (grandParent == nil)
        root = child;
    else if (node == grandParent->left)
        grandParent->left = child;
    else
        grandParent->right = child;

    node->right = leftGrandChild;
    if (leftGrandChild != nil)
        leftGrandChild->parent = node;
}

void RBTree::rightRotate(TreeNode *node) {
    TreeNode *grandParent = node->parent;
    TreeNode *child = node->left;
    TreeNode *rightGrandChild = child->right;

    child->right = node;
    node->parent = child;

    // Promote child to be node
    child->parent = grandParent;
    if (grandParent == nil)
        root = child;
    else if (node == grandParent->left)
        grandParent->left = child;
    else
        grandParent->right = child;

    node->left = rightGrandChild;
    if (rightGrandChild != nil)
        rightGrandChild->parent = node;
}
TreeNode *RBTree::getNode(int val) {
    TreeNode *curr = root;
    while (curr != nil) {
        if (curr->val == val)
            return curr;
        else if (curr->val < val)
            curr = curr->right;
        else
            curr = curr->left;
    }
    return nil;
}
TreeNode *RBTree::getSuccessor(TreeNode *node) {
    while (node != nil)
        node = node->left;
    return node;
}

bool RBTree::search(int val) { return getNode(val) != nil; }

void RBTree::insert(int val) {
    TreeNode *node = createNewNode(val);
    TreeNode *curr = root;

    // NOTE: Normal BST insertion
    TreeNode *parent = nil;
    while (curr != nil) {
        parent = curr;
        if (curr->val < val)
            curr = curr->right;
        else
            curr = curr->left;
    }

    node->parent = parent;

    if (parent == nil)
        root = node;
    else if (val < parent->val)
        parent->left = node;
    else
        parent->right = node;

    size++;
    // 1 Node
    if (node->parent == nil) {
        node->color = BLACK;
        return;
    }
    // 2 Node
    if (node->parent->parent == nil)
        return;
    fixInsertion(node);
}
void RBTree::fixInsertion(TreeNode *node) {
    while (node != root && node->parent->color == RED) {
        TreeNode *parent = node->parent;
        TreeNode *grandParent = parent->parent;

        bool parentIsLeft = (parent == grandParent->left);
        TreeNode *uncle = parentIsLeft ? grandParent->right : grandParent->left;

        if (uncle->color == RED) {
            parent->color = BLACK;
            uncle->color = BLACK;
            grandParent->color = RED;
            node = grandParent;
        } else {
            // NOTE: Triangle case:
            //              GP                GP
            //             /  \              / \
            //            P    U    or      U   P
            //             \                   /
            //              C                 C
            //  If triangle case, rotate to transfrom into line case
            if (parentIsLeft ? node == parent->right : node == parent->left) {
                // NOTE: After rotating, the parent comes down, which is where
                // we want the node to be in the line case
                node = parent;
                parentIsLeft ? leftRotate(node) : rightRotate(node);
                parent = node->parent;
            }
            // NOTE: Line case:
            //              GP                GP
            //             /  \              / \
            //            P    U    or      U   P
            //           /                       \
            //          C                         C
            parent->color = BLACK;
            grandParent->color = RED;
            parentIsLeft ? rightRotate(grandParent) : leftRotate(grandParent);
        }
    }
    root->color = BLACK;
}
void RBTree::transplant(TreeNode *target, TreeNode *source) {
    TreeNode *grandParent = target->parent;
    // Only 2 nodes in tree, target is going to be deleted
    if (grandParent == nil)
        root = source;
    else if (target == grandParent->left)
        grandParent->left = source;
    else
        grandParent->right = source;
    source->parent = grandParent;
}

void RBTree::remove(int val) {
    TreeNode *toDelete = getNode(val);
    if (toDelete == nil)
        return;
    TreeNode *successor = toDelete;
    TreeNode *replacement;
    COLOR originalColor = successor->color;

    if (toDelete->left == nil) {
        replacement = toDelete->right;
        transplant(toDelete, replacement);
    } else if (toDelete->right == nil) {
        replacement = toDelete->left;
        transplant(toDelete, replacement);
    } else {
        successor = getSuccessor(toDelete->right);
        originalColor = successor->color;
        // If the successor has a child, it'd have to be on the right
        replacement = successor->right;
        if (successor->parent == toDelete) {
            // Might set nil's parent to successor, used to handle double black
            // case
            replacement->parent = successor;
        } else {
            // Replace successor with the right child
            transplant(successor, replacement);
            // "Promote" successor to the node being deleted
            successor->right = toDelete->right;
            successor->right->parent = successor;
        }
        transplant(toDelete, successor);
        successor->left = toDelete->left;
        successor->left->parent = successor;
        successor->color = toDelete->color;
    }

    if (originalColor == BLACK)
        fixDeletion(replacement);
    size--;
}

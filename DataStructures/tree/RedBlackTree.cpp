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
    while (node->left != nil)
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
    // NOTE: Replace the target's parent to point to source instead of target
    //              P                   P
    //            // \\              / || \\
    //           T     O    ==>     T  ||  O
    //         // \\              // \ ||
    //         O   S              O    S
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
    // NOTE: Normal BST deletion followed by fixing RB violations
    TreeNode *toDelete = getNode(val);
    if (toDelete == nil)
        return;
    TreeNode *successor = toDelete;
    TreeNode *replacement;
    COLOR originalColor = successor->color;
    // NOTE: If any node has a single child, it'd have to be a BLACK node with a
    // RED child,
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
            replacement->parent = successor;
        } else {
            transplant(successor, replacement);
            successor->right = toDelete->right;
            successor->right->parent = successor;
        }
        // Physically moving the successor to to-be-deleted node
        transplant(toDelete, successor);
        successor->left = toDelete->left;
        successor->left->parent = successor;
        successor->color = toDelete->color;
    }
    delete toDelete;

    // NOTE: If the deleted node was RED, there will be no RB violations
    // The black height doesn't change. And there won't be any red-red violation
    // given the tree was valid. Also, the node would have to be a leaf.
    if (originalColor == BLACK)
        fixDeletion(replacement);
    size--;
}

void RBTree::fixDeletion(TreeNode *node) {
    // NOTE: If a black node is deleted from the tree, the black height along
    // that path decreases by one. This "lost blackness" of the deleted node is
    // pushed to its replacement (node parameter here), so the replacement node
    // holds the extra weight of a black node.

    // NOTE: HAT analogy
    // - Think of a node having colour BLACK as wearing a HAT, meaning every
    // path from a node to nil would have to have the same number of hats.
    // - If a node with HAT is deleted, you can't just remove the hat as it
    // would violate the black height property.
    // - So you make the replacement node wear the HAT.
    // - If the node previously didn't have any HAT, it would just accept the
    // HAT without any problem.
    // - If it already had a HAT, it would be now wearing TWO HATS (double black
    // case)

    // NOTE: 1. If the node is RED, it can "absorb" this "extra weight of black
    // node" by recoloring to black
    // 2. If the node is ROOT, you can just ignore the loss of black node as it
    // effects every path in the tree equally
    // 3. If the node is BLACK, double black case. Handled inside the loop
    while (node != root && node->color == BLACK) {
        TreeNode *parent = node->parent;
        bool isLeft = node == parent->left;
        TreeNode *sibling = isLeft ? parent->right : parent->left;

        // NOTE: Sibling is red, reduces to one of the following cases
        if (sibling->color == RED) {
            sibling->color = BLACK;
            parent->color = RED;
            isLeft ? leftRotate(parent) : rightRotate(parent);
            sibling = isLeft ? parent->right : parent->left;
        }

        // NOTE: Sibling is black and both nephews are black
        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
            // Decreases the black height of sibling
            sibling->color = RED;
            node = parent;
        } else {
            // NOTE: Only one of the nephew is black
            TreeNode *farNephew = isLeft ? sibling->right : sibling->left;
            TreeNode *nearNephew = isLeft ? sibling->left : sibling->right;

            // NOTE: Far nephew is black, reduces to last one
            if (farNephew->color == BLACK) {
                nearNephew->color = BLACK;
                sibling->color = RED;
                isLeft ? rightRotate(sibling) : leftRotate(sibling);
                sibling = isLeft ? parent->right : parent->left;
            }

            // NOTE: Near nephew is black
            sibling->color = parent->color;
            parent->color = BLACK;
            farNephew->color = BLACK;
            isLeft ? leftRotate(parent) : rightRotate(parent);
            node = root;
        }
    }
    node->color = BLACK;
}

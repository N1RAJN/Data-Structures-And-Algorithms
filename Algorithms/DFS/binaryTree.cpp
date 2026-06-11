#include "../../DataStructures/binaryTree.h"
#include <bits/stdc++.h>

TreeNode *dfs(TreeNode *node, int needle) {
    if (!node)
        return nullptr;
    if (node->val == needle)
        return node;
    TreeNode *res = dfs(node->left, needle);
    if (res)
        return res;
    return dfs(node->right, needle);
}

// Find node with the given value, assuming unique node values
TreeNode *findNode(TreeNode *root, int needle) { return dfs(root, needle); }

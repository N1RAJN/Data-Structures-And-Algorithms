#include "../../DataStructures/tree/binaryTree.h"
#include <bits/stdc++.h>
using namespace std;

TreeNode *bfs(TreeNode *root, int needle) {
    if (!root)
        return nullptr;

    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode *node = q.front();
        q.pop();

        if (node->val == needle)
            return node;
        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    return nullptr;
}

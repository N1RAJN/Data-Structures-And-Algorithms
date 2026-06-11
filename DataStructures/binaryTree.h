#pragma once
struct TreeNode {
    int val;
    TreeNode *right;
    TreeNode *left;

    TreeNode() : val(0), right(nullptr), left(nullptr) {}
    TreeNode(int _val) : val(_val), right(nullptr), left(nullptr) {};
    TreeNode(int _val, TreeNode *_right, TreeNode *_left)
        : val(_val), right(_right), left(_left) {};
};

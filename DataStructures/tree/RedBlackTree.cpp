#include <bits/stdc++.h>
using namespace std;

enum COLOR { RED, BLACK };
struct TreeNode {
    COLOR color;
    int val;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : color(BLACK), val(), left(nullptr), right(nullptr) {}
    TreeNode(int _val) : color(RED), val(_val), left(nullptr), right(nullptr) {}
};

class RedBlackTree {
    TreeNode *root;
    int size;

    void leftRotate(TreeNode *node);
    void rightRotate(TreeNode *node);

  public:
    RedBlackTree() : root(nullptr), size(0) {}
    void insert(int val);
    bool search(int val);
    void remove(int val);
};

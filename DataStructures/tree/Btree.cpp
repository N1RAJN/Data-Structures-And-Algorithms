#include <bits/stdc++.h>
using namespace std;

class BTree {
    struct BTreeNode {
        bool is_leaf;
        vector<int> keys;
        vector<BTreeNode *> children;

        BTreeNode(int _order, bool _is_leaf) : is_leaf(_is_leaf) {}
    };
    int order; // Maximum number of children
    uint size;
    BTreeNode *root;

    struct SplitResult {
        bool split_occured = false;
        int promoted_key;
        BTreeNode *right_child;
    };

    int minKeys() { return order / 2 - 1; };
    int maxKeys() { return order - 1; };

    SplitResult split_child(BTreeNode *node) {
        int mid = order / 2;

        SplitResult res;
        res.split_occured = true;
        res.promoted_key = node->keys[mid];
        res.right_child = new BTreeNode(order, node->is_leaf);

        // Move right half of node to right sibling
        res.right_child->keys.assign(node->keys.begin() + mid + 1,
                                     node->keys.end());
        node->keys.erase(node->keys.begin() + mid, node->keys.end());

        // If not a leaf, move the children as well
        if (!node->is_leaf) {
            res.right_child->children.assign(node->children.begin() + mid + 1,
                                             node->children.end());
            node->children.erase(node->children.begin() + mid + 1,
                                 node->children.end());
        }
        return res;
    }

    int get_max_key(BTreeNode *node) {
        BTreeNode *curr = node;
        while (!curr->is_leaf)
            curr = curr->children.back();
        return curr->keys.back();
    }
    void merge_to_left_child(BTreeNode *parent, int left_idx) {
        BTreeNode *left_child = parent->children[left_idx];
        BTreeNode *right_child = parent->children[left_idx + 1];

        left_child->keys.push_back(parent->keys[left_idx]);
        parent->children.erase(parent->children.begin() + left_idx + 1);
        parent->keys.erase(parent->keys.begin() + left_idx);

        for (int k : right_child->keys)
            left_child->keys.push_back(k);

        if (!right_child->is_leaf) {
            for (auto &child : right_child->children)
                left_child->children.push_back(child);
        }
        delete right_child;
    }

    void fix_underflow(BTreeNode *parent, int child_idx) {
        BTreeNode *child = parent->children[child_idx];
        int min_keys = minKeys();
        if (child->keys.size() >= min_keys)
            return;

        if (child_idx > 0 &&
            parent->children[child_idx - 1]->keys.size() > min_keys) {
            BTreeNode *left_sibling = parent->children[child_idx - 1];

            // Take key from parent
            child->keys.insert(child->keys.begin(),
                               parent->keys[child_idx - 1]);

            // Parent takes key from left sibling
            parent->keys[child_idx - 1] = left_sibling->keys.back();
            left_sibling->keys.pop_back();

            if (!child->is_leaf) {
                child->children.insert(child->children.begin(),
                                       left_sibling->children.back());
                left_sibling->children.pop_back();
            }
        } else if (child_idx < parent->children.size() - 1 &&
                   parent->children[child_idx + 1]->keys.size() > min_keys) {

            BTreeNode *right_sibling = parent->children[child_idx + 1];
            child->keys.push_back(parent->keys[child_idx]);
            parent->keys[child_idx] = right_sibling->keys.front();
            right_sibling->keys.erase(right_sibling->keys.begin());

            if (!child->is_leaf) {
                child->children.push_back(right_sibling->children.front());
                right_sibling->children.erase(right_sibling->children.begin());
            }

        } else {
            if (child_idx > 0)
                merge_to_left_child(parent, child_idx - 1);
            else
                merge_to_left_child(parent, child_idx);
        }
    }

    int _search(BTreeNode *node, int key) {
        int i = 0;
        while (i < node->keys.size() && node->keys[i] < key)
            i++;
        return i;
    }

    SplitResult _insert(BTreeNode *node, int key) {
        int i = _search(node, key);
        if (i < node->keys.size() && key == node->keys[i])
            return SplitResult{};

        if (node->is_leaf) {
            node->keys.insert(node->keys.begin() + i, key);
        } else {
            SplitResult res = _insert(node->children[i], key);

            if (res.split_occured) {
                node->keys.insert(node->keys.begin() + i, res.promoted_key);
                node->children.insert(node->children.begin() + i + 1,
                                      res.right_child);
            }
        }

        if (node->keys.size() == order) {
            return split_child(node);
        }
        return SplitResult{};
    }

    bool _remove(BTreeNode *node, int key) {
        int i = _search(node, key);

        if (node->is_leaf) {
            if (i < node->keys.size() && node->keys[i] == key) {
                node->keys.erase(node->keys.begin() + i);
                return true;
            }
            return false;
        }
        bool removed = false;
        if (i < node->keys.size() && node->keys[i] == key) {
            int predecessor_key = get_max_key(node->children[i]);
            node->keys[i] = predecessor_key;

            _remove(node->children[i], predecessor_key);
            fix_underflow(node, i);
            removed = true;
        } else {
            removed = _remove(node->children[i], key);
            if (removed)
                fix_underflow(node, i);
        }
        return removed;
    }

  public:
    BTree(int _order) : size(0), order(_order) {
        root = new BTreeNode(_order, true);
    }

    bool search(int val, int &index) {
        index = -1;
        BTreeNode *curr = root;
        while (curr) {
            // Linear search through the keys
            // 1. Either you find the key inside this node
            // 2. Or you find the index of the child which potentially has it

            int i = _search(curr, val);
            if (i < curr->keys.size() && curr->keys[i] == val) {
                index = i;
                return curr;
            }
            if (curr->is_leaf)
                return {};

            // Search in the child
            curr = curr->children[i];
        }
        return {};
    };

    void insert(int val) {
        SplitResult res = _insert(root, val);

        // Check if the root was split
        if (res.split_occured) {
            BTreeNode *new_root = new BTreeNode(order, false);
            new_root->keys.push_back(res.promoted_key);
            new_root->children.push_back(root);
            new_root->children.push_back(res.right_child);
            root = new_root;
        }
    };
    bool remove(int val) {
        bool removed = _remove(root, val);

        if (root->keys.empty() && !root->is_leaf)
            root = root->children[0];

        return removed;
    };
};

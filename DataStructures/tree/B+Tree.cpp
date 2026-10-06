#include <bits/stdc++.h>
using namespace std;

class BPTree {
    struct BPTreeNode {
        vector<int> keys;
        bool is_leaf;

        BPTreeNode(bool _is_leaf) : is_leaf(_is_leaf) {}
    };

    struct BPTreeLeafNode : BPTreeNode {
        vector<string> values;
        BPTreeLeafNode *next_leaf;

        BPTreeLeafNode() : BPTreeNode(true) {}
    };

    struct BPTreeInternalNode : BPTreeNode {
        vector<BPTreeNode *> childrens;

        BPTreeInternalNode() : BPTreeNode(false) {}
    };

    int order;
    BPTreeNode *root;

    struct SplitResult {
        bool split_occured = false;
        int promoted_key;
        BPTreeNode *right_child;
    };

    int minKeys() { return order / 2 - 1; };
    int maxKeys() { return order - 1; };

    SplitResult split_node(BPTreeNode *node) {
        int mid = order / 2;

        SplitResult res;
        res.promoted_key = node->keys[mid];
        res.split_occured = true;
        res.right_child = new BPTreeNode(node->is_leaf);

        // Copy keys
        res.right_child->keys.assign(node->keys.begin() + mid,
                                     node->keys.end());
        node->keys.erase(node->keys.begin(), node->keys.begin() + mid);

        // Copy values or children pointer based on node type
        if (node->is_leaf) {
            BPTreeLeafNode *temp = static_cast<BPTreeLeafNode *>(node);

            (static_cast<BPTreeLeafNode *>(res.right_child))
                ->values.assign(temp->values.begin() + mid, temp->values.end());

            temp->values.erase(temp->values.begin(),
                               temp->values.begin() + mid);
        } else {
            BPTreeInternalNode *temp = static_cast<BPTreeInternalNode *>(node);

            (static_cast<BPTreeInternalNode *>(res.right_child))
                ->childrens.assign(temp->childrens.begin() + mid,
                                   temp->childrens.end());

            temp->childrens.erase(temp->childrens.begin(),
                                  temp->childrens.begin() + mid);
        }
        return SplitResult{};
    }

    SplitResult _insert(BPTreeNode *node, int key, string value) {
        int idx = *upper_bound(node->keys.begin(), node->keys.end(), key);
        if (node->is_leaf) {
            if (idx > 0 && node->keys[idx - 1] == key) {
                (static_cast<BPTreeLeafNode *>(node))->values[idx - 1] = value;
            } else {
                BPTreeLeafNode *leaf = static_cast<BPTreeLeafNode *>(node);
                leaf->values.insert(leaf->values.begin() + idx, value);
            }
        } else {
            SplitResult res = _insert(
                (static_cast<BPTreeInternalNode *>(node))->childrens[idx], key,
                value);

            if (res.split_occured) {
                node->keys.insert(node->keys.begin() + idx, res.promoted_key);

                BPTreeInternalNode *inNode =
                    static_cast<BPTreeInternalNode *>(node);
                inNode->childrens.insert(inNode->childrens.begin() + idx,
                                         res.right_child);
            }
        }

        if (node->keys.size() == order)
            return split_node(node);

        return SplitResult{};
    }

  public:
    BPTree(int _order) : order(_order) { root = new BPTreeNode(true); }

    optional<string> search(int key) {
        BPTreeNode *curr = root;

        // 1. Find the leaf node to search
        while (!curr->is_leaf) {
            int idx = *upper_bound(curr->keys.begin(), curr->keys.end(), key);
            curr = (static_cast<BPTreeInternalNode *>(curr))->childrens[idx];
        }

        // 2. Search inside the leaf
        for (int i = 0; i < curr->keys.size(); ++i)
            if (curr->keys[i] == key)
                return (static_cast<BPTreeLeafNode *>(curr))->values[i];
        return {};
    }

    void insert(int key, string value) {
        SplitResult res = _insert(root, key, value);

        if (res.split_occured) {
            BPTreeNode *new_root = new BPTreeNode(false);
            new_root->keys.push_back(res.promoted_key);

            (static_cast<BPTreeInternalNode *>(new_root))
                ->childrens.push_back(root);

            (static_cast<BPTreeInternalNode *>(new_root))
                ->childrens.push_back(res.right_child);
            root = new_root;
        }
    }

    void remove(int key) {}
};

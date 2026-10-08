#include <algorithm>
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

        BPTreeLeafNode() : BPTreeNode(true), next_leaf(nullptr) {}
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

    int minKeys() { return (order - 1) / 2; };
    int maxKeys() { return order - 1; };

    int get_min_key(BPTreeNode *node) {
        auto *curr = node;
        while (!curr->is_leaf)
            curr = (static_cast<BPTreeInternalNode *>(curr))->childrens.front();
        return curr->keys.front();
    }

    SplitResult split_node(BPTreeNode *node) {
        int mid = order / 2;

        SplitResult res;
        res.promoted_key = node->keys[mid];
        res.split_occured = true;
        res.right_child = node->is_leaf
                              ? (BPTreeNode *)new BPTreeLeafNode()
                              : (BPTreeNode *)new BPTreeInternalNode();

        // Move half the keys to right child
        res.right_child->keys.assign(node->keys.begin() + mid + 1,
                                     node->keys.end());
        node->keys.erase(node->keys.begin() + mid, node->keys.end());

        // Copy values or children pointer based on node type
        if (node->is_leaf) {
            auto *curr = static_cast<BPTreeLeafNode *>(node);
            auto *right_leaf = static_cast<BPTreeLeafNode *>(res.right_child);

            // Separater key must be copied in the leaf node
            res.right_child->keys.insert(res.right_child->keys.begin(),
                                         res.promoted_key);

            right_leaf->values.assign(curr->values.begin() + mid,
                                      curr->values.end());
            curr->values.erase(curr->values.begin() + mid, curr->values.end());

            // Add the new node in the "linked list"
            right_leaf->next_leaf = curr->next_leaf;
            curr->next_leaf = right_leaf;

        } else {
            auto *curr = static_cast<BPTreeInternalNode *>(node);
            auto *right_internal =
                static_cast<BPTreeInternalNode *>(res.right_child);

            right_internal->childrens.assign(curr->childrens.begin() + mid + 1,
                                             curr->childrens.end());
            curr->childrens.erase(curr->childrens.begin() + mid + 1,
                                  curr->childrens.end());
        }
        return res;
    }

    void merge_nodes(BPTreeInternalNode *parent, int left_idx) {
        BPTreeNode *left_child = parent->childrens[left_idx];
        BPTreeNode *right_child = parent->childrens[left_idx + 1];

        // WARN: (Right) Leaf already contains the separater key
        if (!left_child->is_leaf)
            left_child->keys.push_back(parent->keys[left_idx]);

        for (int k : right_child->keys)
            left_child->keys.push_back(k);

        if (left_child->is_leaf) {
            BPTreeLeafNode *left = (static_cast<BPTreeLeafNode *>(left_child));
            BPTreeLeafNode *right =
                (static_cast<BPTreeLeafNode *>(right_child));

            for (auto value : right->values)
                left->values.push_back(value);

            left->next_leaf = right->next_leaf;

        } else {
            BPTreeInternalNode *left =
                (static_cast<BPTreeInternalNode *>(left_child));
            BPTreeInternalNode *right =
                (static_cast<BPTreeInternalNode *>(right_child));

            for (auto child : right->childrens)
                left->childrens.push_back(child);
        }

        parent->keys.erase(parent->keys.begin() + left_idx);
        parent->childrens.erase(parent->childrens.begin() + left_idx + 1);

        delete right_child;
    }

    void fix_underflow(BPTreeInternalNode *parent, int child_idx) {
        BPTreeNode *child = parent->childrens[child_idx];

        // Borrow from left sibling
        if (child_idx > 0 &&
            parent->childrens[child_idx - 1]->keys.size() > minKeys()) {

            BPTreeNode *left_sibling = parent->childrens[child_idx - 1];

            if (child->is_leaf) {
                auto *left = static_cast<BPTreeLeafNode *>(left_sibling);
                auto *curr = static_cast<BPTreeLeafNode *>(child);

                // Move last key and value from left
                curr->keys.insert(curr->keys.begin(), left->keys.back());
                curr->values.insert(curr->values.begin(), left->values.back());
                left->keys.pop_back();
                left->values.pop_back();

                // Separator becomes the new minimum of the current leaf
                parent->keys[child_idx - 1] = curr->keys.front();
            } else {
                auto *left = static_cast<BPTreeInternalNode *>(left_sibling);
                auto *curr = static_cast<BPTreeInternalNode *>(child);

                // Internal rotate
                // 1. Bring separater from parent down to current
                // 2. Last key from left sibling becomes new separator
                curr->keys.insert(curr->keys.begin(),
                                  parent->keys[child_idx - 1]);
                parent->keys[child_idx - 1] = left->keys.back();
                left->keys.pop_back();

                curr->childrens.insert(curr->childrens.begin(),
                                       left->childrens.back());
                left->childrens.pop_back();
            }
        }
        // Borrow from right sibling
        else if (child_idx < parent->childrens.size() - 1 &&
                 parent->childrens[child_idx + 1]->keys.size() > minKeys()) {

            BPTreeNode *right_sibling = parent->childrens[child_idx + 1];

            if (child->is_leaf) {
                auto *right = static_cast<BPTreeLeafNode *>(right_sibling);
                auto *curr = static_cast<BPTreeLeafNode *>(child);

                // Move first key and value from right
                curr->keys.push_back(right->keys.front());
                curr->values.push_back(right->values.front());
                right->keys.erase(right->keys.begin());
                right->values.erase(right->values.begin());

                // NOTE: Separater in the parent must be the minimum value of
                // the right sibling AFTER the move. (Implicitly true when
                // borrowing from left node)
                // Parent:     [ ... |  S  | ... ]
                //               /            \
                // Left leaf:  [a b]         Right leaf: [S  c  d]
                // After borrowing:
                // Left leaf:  [a b S]         Right leaf: [c  d]
                //
                // If S is left in the parent, search for keys in [S, c) would
                // go in the right leaf, which is incorrect

                // Assign the new minimum key (after removing the borrowed one)
                parent->keys[child_idx] = right->keys.front();
            } else {
                auto *right = static_cast<BPTreeInternalNode *>(right_sibling);
                auto *curr = static_cast<BPTreeInternalNode *>(child);

                // Internal rotate
                curr->keys.push_back(parent->keys[child_idx]);
                parent->keys[child_idx] = right->keys.front();
                right->keys.erase(right->keys.begin());

                curr->childrens.push_back(right->childrens.front());
                right->childrens.erase(right->childrens.begin());
            }
        } else {
            if (child_idx < parent->keys.size())
                merge_nodes(parent, child_idx);
            else
                merge_nodes(parent, child_idx - 1);
        }
    }

    SplitResult _insert(BPTreeNode *node, int key, string value) {
        int idx = upper_bound(node->keys.begin(), node->keys.end(), key) -
                  node->keys.begin();
        if (node->is_leaf) {
            // Update value of existing key
            if (idx > 0 && node->keys[idx - 1] == key) {
                (static_cast<BPTreeLeafNode *>(node))->values[idx - 1] = value;
            }
            // New insertion
            else {
                BPTreeLeafNode *leaf = static_cast<BPTreeLeafNode *>(node);
                leaf->keys.insert(leaf->keys.begin() + idx, key);
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
                inNode->childrens.insert(inNode->childrens.begin() + idx + 1,
                                         res.right_child);
            }
        }

        if (node->keys.size() == order)
            return split_node(node);

        return SplitResult{};
    }

    bool _remove(BPTreeNode *node, int key) {
        int idx = upper_bound(node->keys.begin(), node->keys.end(), key) -
                  node->keys.begin();

        if (node->is_leaf) {
            if (idx > 0 && node->keys[idx - 1] == key) {
                BPTreeLeafNode *curr = static_cast<BPTreeLeafNode *>(node);
                curr->keys.erase(curr->keys.begin() + idx - 1);
                curr->values.erase(curr->values.begin() + idx - 1);
                return true;
            }
            return false;
        }
        BPTreeInternalNode *int_node = static_cast<BPTreeInternalNode *>(node);
        bool removed = _remove(int_node->childrens[idx], key);

        if (!removed) {
            return false;
        }

        // Update the separator at parent
        // FIXME: (at some point) Propagate the change in minimum key uptowards
        // the ancestors
        if (idx > 0 && node->keys[idx - 1] == key) {
            node->keys[idx - 1] = get_min_key(int_node->childrens[idx]);
        }

        // Fix if child node underflows
        if (int_node->childrens[idx]->keys.size() < minKeys())
            fix_underflow(int_node, idx);

        return true;
    }

  public:
    BPTree(int _order) : order(_order) {
        root = (BPTreeNode *)new BPTreeLeafNode();
    }

    optional<string> search(int key) {
        BPTreeNode *curr = root;

        // 1. Find the leaf node to search
        while (!curr->is_leaf) {
            int idx = upper_bound(curr->keys.begin(), curr->keys.end(), key) -
                      curr->keys.begin();
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
            BPTreeNode *new_root = (BPTreeNode *)(new BPTreeInternalNode());
            new_root->keys.push_back(res.promoted_key);

            (static_cast<BPTreeInternalNode *>(new_root))
                ->childrens.push_back(root);

            (static_cast<BPTreeInternalNode *>(new_root))
                ->childrens.push_back(res.right_child);
            root = new_root;
        }
    }

    bool remove(int key) {
        bool removed = _remove(root, key);

        if (root->keys.empty() && !root->is_leaf) {
            BPTreeNode *old_root = root;
            root = static_cast<BPTreeInternalNode *>(root)->childrens[0];
            delete old_root;
        }
        return removed;
    }
};

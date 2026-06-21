// NOTE: Also called Trie (/try/)
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    static const int size = 26;
    bool isWord;
    int wordCount;
    TreeNode *children[size];
    TreeNode() : isWord(false), wordCount(0) {
        for (int i = 0; i < size; ++i)
            children[i] = nullptr;
    }
};

class PrefixTree {
    TreeNode *root;
    int getIndex(char c) { return c - 'a'; }
    char getChar(int i) { return i + 'a'; }
    void clear(TreeNode *curr) {
        if (!curr)
            return;
        for (int i = 0; i < TreeNode::size; ++i)
            if (curr->children[i])
                clear(curr->children[i]);
        delete curr;
    }

    void dfs(TreeNode *curr, vector<string> &result, const string &prefix,
             string &suffix);

    TreeNode *removeDFS(TreeNode *curr, const string &word, int i, bool &found);

  public:
    PrefixTree() { root = new TreeNode(); }
    ~PrefixTree() { clear(root); }
    void insert(string word);
    bool search(string word);
    void remove(string word);
    bool startsWith(string prefix);
    vector<string> getAllWordWithPrefix(string prefix);
    int countWordStartingWith(string prefix);
};

void PrefixTree::dfs(TreeNode *curr, vector<string> &result,
                     const string &prefix, string &suffix) {
    if (curr->isWord)
        result.push_back(prefix + suffix);
    for (int i = 0; i < TreeNode::size; ++i) {
        if (curr->children[i]) {
            suffix.push_back(getChar(i));
            dfs(curr->children[i], result, prefix, suffix);
            suffix.pop_back();
        }
    }
}

TreeNode *PrefixTree::removeDFS(TreeNode *curr, const string &word, int i,
                                bool &found) {
    if (!curr)
        return nullptr;

    if (i == word.size()) {
        if (curr->isWord) {
            curr->isWord = false;
            curr->wordCount--;
            found = true;
        }
        if (curr != root && curr->wordCount == 0) {
            delete curr;
            curr = nullptr;
        }
        return curr;
    }
    int index = getIndex(word[i]);
    curr->children[index] =
        removeDFS(curr->children[index], word, i + 1, found);
    if (found)
        curr->wordCount--;
    if (curr != root && curr->wordCount == 0 && !curr->isWord) {
        delete curr;
        curr = nullptr;
    }

    return curr;
}

void PrefixTree::insert(string word) {
    if (word.empty())
        return;
    TreeNode *curr = root;
    vector<TreeNode *> path = {root};
    for (char c : word) {
        int i = getIndex(c);
        if (!curr->children[i]) {
            curr->children[i] = new TreeNode();
        }
        curr = curr->children[i];
        path.push_back(curr);
    }
    if (curr->isWord)
        return;
    curr->isWord = true;
    for (TreeNode *node : path)
        node->wordCount++;
}

bool PrefixTree::search(string word) {
    if (word.empty())
        return true;
    TreeNode *curr = root;
    for (char c : word) {
        int i = getIndex(c);
        if (curr->children[i])
            curr = curr->children[i];
        else
            return false;
    }
    return curr ? curr->isWord : false;
}

void PrefixTree::remove(string word) {
    if (word.empty())
        return;
    bool found = false;
    root = removeDFS(root, word, 0, found);
}

bool PrefixTree::startsWith(string prefix) {
    if (prefix.empty())
        return true;
    TreeNode *curr = root;
    for (char c : prefix) {
        int i = getIndex(c);
        if (!curr->children[i])
            return false;
        curr = curr->children[i];
    }
    return curr != nullptr;
}

vector<string> PrefixTree::getAllWordWithPrefix(string prefix) {
    vector<string> result;
    TreeNode *curr = root;
    for (char c : prefix) {
        int i = getIndex(c);
        if (!curr->children[i])
            return result;
        curr = curr->children[i];
    }
    string suffix = "";
    dfs(curr, result, prefix, suffix);
    return result;
}
int PrefixTree::countWordStartingWith(string prefix) {
    if (prefix.empty())
        return root->wordCount;
    TreeNode *curr = root;
    for (char c : prefix) {
        int i = getIndex(c);
        if (!curr->children[i])
            return 0;
        curr = curr->children[i];
    }
    return curr->wordCount;
}

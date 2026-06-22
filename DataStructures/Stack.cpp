#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *prev;

    Node() : val(0), prev(nullptr) {}
    Node(int _val) : val(_val), prev(nullptr) {}
};

class Stack {
    Node *top;
    int size;

  public:
    Stack() : top(nullptr), size(0) {}
    void push(int val);
    optional<int> pop();
};

void Stack::push(int val) {
    Node *node = new Node(val);
    node->prev = top;
    top = node;
    size++;
}
optional<int> Stack::pop() {
    if (size == 0)
        return {};
    int val = top->val;

    Node *toDelete = top;
    top = top->prev;
    delete toDelete;
    size--;

    return val;
}

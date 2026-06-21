#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next;

    Node() : val(), next(nullptr) {};
    Node(int _val) : val(_val), next(nullptr) {};
};

class LinkedList {
    Node *tail;
    int size;

  public:
    LinkedList() : tail(nullptr), size(0) {}
    LinkedList(const vector<int> &nums);
    void append(int val);
    void prepend(int val);
    optional<int> pop_back();
    optional<int> pop_front();
};

LinkedList::LinkedList(const vector<int> &nums) {
    if (nums.empty()) {
        tail = nullptr;
        return;
    }
    Node *curr = new Node(nums[0]);
    Node *head = curr;
    size = 1;
    for (int i = 1; i < nums.size(); ++i) {
        curr->next = new Node(nums[i]);
        curr = curr->next;
        size++;
    }
    curr->next = head;
    tail = curr;
}

void LinkedList::append(int val) {
    Node *node = new Node(val);
    if (size == 0) {
        tail = node;
        tail->next = node;
    } else {
        node->next = tail->next;
        tail->next = node;
        tail = node;
    }
    size++;
}

void LinkedList::prepend(int val) {
    Node *node = new Node(val);
    if (size == 0) {
        tail = node;
        tail->next = node;
    } else {
        node->next = tail->next;
        tail->next = node;
    }
    size++;
}

optional<int> LinkedList::pop_front() {
    if (size == 0)
        return {};
    Node *head = tail->next;
    int val = head->val;

    if (size == 1) {
        tail = nullptr;
    } else {
        tail->next = head->next;
    }

    delete head;
    size--;
    return val;
}

optional<int> LinkedList::pop_back() {
    if (size == 0)
        return {};

    int val = tail->val;
    Node *toDelete = tail;
    if (size == 1) {
        tail = nullptr;
    } else {
        Node *prev = tail->next;
        while (prev->next != tail)
            prev = prev->next;

        prev->next = tail->next;
        tail = prev;
    }

    delete toDelete;
    size--;
    return val;
}

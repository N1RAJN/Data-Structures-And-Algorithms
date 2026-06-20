#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next;

    Node() : val(), next(nullptr) {};
    Node(int _val) : val(_val), next(nullptr) {};
};

class LinkedList {
    Node *head;
    int size;

  public:
    LinkedList() : head(nullptr), size(0) {}
    LinkedList(const vector<int> &nums);
    void insert(int index, int val);
    optional<int> remove(int index);
    void prepend(int val);
    void print();
};

LinkedList::LinkedList(const vector<int> &nums) {
    if (nums.empty()) {
        head = nullptr;
        return;
    }
    head = new Node(nums[0]);
    size++;
    Node *curr = head;
    for (int i = 1; i < nums.size(); ++i) {
        curr->next = new Node(nums[i]);
        curr = curr->next;
        size++;
    }
}

void LinkedList::insert(int index, int val) {
    if (index < 0 || index > size) {
        cout << "Out of bounds\n";
        return;
    }
    int i = 0;
    Node *curr = head;
    while (i < index - 1 && curr != nullptr) {
        curr = curr->next;
        i++;
    }
    if (i == 0)
        prepend(val);
    else {
        Node *node = new Node(val);
        node->next = curr->next;
        curr->next = node;
        size++;
    }
}

optional<int> LinkedList::remove(int index) {
    if (index < 0 || index >= size)
        return {};
    int i = 0;
    Node *curr = head;
    while (i < index - 1 && curr != nullptr) {
        curr = curr->next;
        i++;
    }
    int val;
    if (i == 0) {
        val = head->val;
        delete head;
        head = nullptr;
    } else {
        Node *toDelete = curr->next;
        delete curr->next;
        curr->next = toDelete->next;
        val = toDelete->val;
    }
    size--;
    return val;
}

void LinkedList::prepend(int val) {
    if (size == 0)
        head = new Node(val);
    else {
        Node *node = new Node(val);
        node->next = head;
        head = node;
    }
    size++;
}

void LinkedList::print() {
    if (size == 0)
        return;
    Node *curr = head;
    while (curr) {
        cout << curr->val << " -> ";
        curr = curr->next;
    }
    cout << "\n";
}

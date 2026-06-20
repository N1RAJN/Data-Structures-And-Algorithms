#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *next;
    Node *prev;

    Node() : val(), next(nullptr), prev(nullptr) {};
    Node(int _val) : val(_val), next(nullptr), prev(nullptr) {};
};

class LinkedList {
    Node *head;
    Node *tail;
    int size;

  public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    LinkedList(const vector<int> &nums);
    void insert(int index, int val);
    void prepend(int val);
    void append(int val);
    optional<int> remove(int index);
    optional<int> pop_back();
    optional<int> pop_front();
    void print();
};

LinkedList::LinkedList(const vector<int> &nums) {
    if (nums.empty()) {
        head = nullptr;
        tail = head;
        return;
    }
    head = new Node(nums[0]);
    size++;
    Node *curr = head, *prev = nullptr;
    for (int i = 1; i < nums.size(); ++i) {
        curr->next = new Node(nums[i]);
        curr->prev = prev;
        prev = curr;
        curr = curr->next;
        size++;
    }
    tail = curr;
}

void LinkedList::insert(int index, int val) {
    if (index < 0 || index > size) {
        cout << "Out of bounds\n";
        return;
    }
    if (index == 0) {
        prepend(val);
        return;
    }
    if (index == size) {
        append(val);
        return;
    }
    int i = 0;
    Node *curr = head;
    while (i < index - 1 && curr != nullptr) {
        curr = curr->next;
        i++;
    }
    Node *node = new Node(val);
    node->next = curr->next;
    curr->next->prev = node;
    node->prev = curr;
    curr->next = node;
    size++;
}

void LinkedList::prepend(int val) {
    if (size == 0) {
        head = new Node(val);
        tail = head;
    } else {
        Node *node = new Node(val);
        node->next = head;
        head->prev = node;
        head = node;
    }
    size++;
}

void LinkedList::append(int val) {
    if (size == 0) {
        head = new Node(val);
        tail = head;
    } else {
        Node *node = new Node(val);
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    size++;
}

optional<int> LinkedList::remove(int index) {
    if (index < 0 || index >= size)
        return {};

    if (index == 0)
        return pop_front();

    if (index == size)
        return pop_back();

    int i = 0;
    Node *curr = head;
    while (i < index - 1 && curr != nullptr) {
        curr = curr->next;
        i++;
    }
    Node *toDelete = curr->next;
    int val = toDelete->val;

    curr->next = toDelete->next;
    toDelete->next->prev = curr;

    delete toDelete;
    size--;
    return val;
}

optional<int> LinkedList::pop_back() {
    if (size == 0)
        return {};
    size--;
    int val = tail->val;
    if (size == 0) {
        head = tail = nullptr;
    } else {
        Node *toDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete toDelete;
    }
    return val;
}

optional<int> LinkedList::pop_front() {
    if (size == 0)
        return {};
    size--;
    int val;
    if (size == 0) {
        val = head->val;
        head = tail = nullptr;
    } else {
        Node *toDelete = head;
        head = head->next;
        head->prev = nullptr;
        delete toDelete;
    }
    return val;
}
void LinkedList::print() {
    if (size == 0)
        return;
    Node *curr = head;
    while (curr) {
        cout << curr->val << " <-> ";
        curr = curr->next;
    }
    cout << "\n";
}

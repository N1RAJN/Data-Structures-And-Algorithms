#include <bits/stdc++.h>
#define capacity 100
class MinHeap {
    // NOTE: Use arrays to represent the heap instead of a tree data structure
    // Why is it possible to do so?
    //  1. Binary heaps are COMPLETE binary trees ,i.e, all the levels are full
    //  filled, except possibly the last level which is filled from left to
    //  right. Which means there's no holes in the array when representing the
    //  heap
    //  2. Hence, the index arithemtic can be used to efficiently find the
    //  parent and child nodes
    // Why use arrays?
    //  1. No overhead of storing reference to child, or parent (less memory
    //  needed)
    //  2. No dealing with pointers
    //  3. Cache locality, (tree is scattered around)
    //  4. Index arithemtic (to get required node) is cheaper than using
    //  pointers, as it only involves a left shift and an addition
    int size;
    int items[capacity];

    int parent(int idx) { return (idx - 1) / 2; }
    int left(int idx) { return 2 * idx + 1; }
    int right(int idx) { return 2 * idx + 2; }

    void heapifyUp(int idx) {
        while (idx > 0) {
            int pIdx = parent(idx);
            // NOTE: Current node is smaller than its parent
            // i.e, doesn't satisfy minHeap property
            if (items[idx] < items[pIdx]) {
                std::swap(items[idx], items[pIdx]);
                idx = pIdx;
            } else
                break;
        }
    }
    void heapifyDown(int idx) {
        for (;;) {
            int l = left(idx);
            int r = right(idx);
            int smallest = idx;

            // NOTE: find the smallest out of the parent, left child and right
            // child
            if (l < size && items[l] < items[smallest])
                smallest = l;
            if (r < size && items[r] < items[smallest])
                smallest = r;
            // NOTE: if the smallest if the parent, minHeap property is
            // satisfied
            if (smallest == idx)
                break;
            // NOTE: If not swap the smallest one to the current node
            std::swap(items[idx], items[smallest]);
            idx = smallest;
        }
    }

  public:
    MinHeap() : size(0) { std::fill(items, items + capacity, 0); }
    MinHeap(int _size) : size(_size) { std::fill(items, items + capacity, 0); }
    MinHeap(std::vector<int> &nums) { heapify(nums); }
    // NOTE: O(n) runtime because math, idk
    void heapify(std::vector<int> &nums) {
        if (nums.size() > capacity) {
            std::cout << "Capacity exceeded";
            return;
        }
        size = nums.size();
        std::copy(nums.begin(), nums.end(), items);
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }
    void insert(int val) {
        if (size == capacity)
            return;
        // NOTE: Insert at the last index (Completeness of binary heap)
        items[size] = val;
        // NOTE: Shift the inserted node to its correct position
        heapifyUp(size);
        size++;
    }

    std::optional<int> remove() {
        if (size == 0) {
            return {};
        }
        int val = items[0];
        size--;
        if (size > 0) {
            // NOTE: Put the last node in the root (Completeness
            // because removing the root would split the tree in two unconnected
            // subtrees)
            items[0] = items[size];
            // NOTE: The above preseves the completeness but breaks minHeap
            // property, so heapify down to fix it
            heapifyDown(0);
        }
        return val;
    }
    std::optional<int> top() {
        if (size == 0)
            return {};
        return items[0];
    }
};

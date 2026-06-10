#include <bits/stdc++.h>
using namespace std;
class LRUCache {
  private:
    struct ListNode {
        int key;
        int val;
        ListNode *next;
        ListNode *prev;

        ListNode(int x, int y) : key(x), val(y), next(nullptr), prev(nullptr) {}
        void operator=(const ListNode &a) {
            val = a.val;
            next = a.next;
            prev = a.prev;
        }
    };
    unordered_map<int, ListNode *> cacheMap;
    ListNode *leastRecent;
    ListNode *mostRecent;
    int capacity;

    void remove(ListNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void insert(ListNode *node) {
        node->prev = mostRecent->prev;
        node->prev->next = node;
        mostRecent->prev = node;
        node->next = mostRecent;
    }

  public:
    LRUCache(int capacity) : capacity(capacity) {
        cacheMap.clear();
        leastRecent = new ListNode(0, 0);
        mostRecent = new ListNode(0, 0);
        leastRecent->next = mostRecent;
        mostRecent->prev = leastRecent;
    }

    ~LRUCache() {
        ListNode *curr = leastRecent;
        while (curr) {
            ListNode *next = curr->next;
            delete curr;
            curr = next;
        }
    }
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end())
            return -1;

        ListNode *node = cacheMap.at(key);
        remove(node);
        insert(node);

        return node->val;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            ListNode *node = cacheMap.at(key);
            remove(node);
        }
        ListNode *node = new ListNode(key, value);
        insert(node);
        cacheMap[key] = node;

        if (cacheMap.size() > capacity) {
            ListNode *toDelete = leastRecent->next;
            remove(toDelete);
            cacheMap.erase(toDelete->key);
            delete toDelete;
        }
    }
};

int main() { return 0; }

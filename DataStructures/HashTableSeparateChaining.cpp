#include <bits/stdc++.h>
using namespace std;
class HashTable {
  private:
    int size;
    static const int BUCKET_COUNT = 100;
    list<pair<string, string>> buckets[BUCKET_COUNT];

    int hash_function(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % BUCKET_COUNT;
        }
        return hash;
    }

  public:
    void insertItem(string key, string value) {
        int hash = hash_function(key);
        auto itr = begin(buckets[hash]);
        for (; itr != end(buckets[hash]); itr++) {
            if (itr->first == key) {
                cout << "Duplicate Key. Value replaced\n";
                itr->second = value;
                return;
            }
        }
        cout << "Inserted item\n";
        buckets[hash].push_back({key, value});
        size++;
    }
    void eraseItem(string key) {
        if (size == 0) {
            cout << "Empty Table.\n";
            return;
        }
        int hash = hash_function(key);
        auto itr = begin(buckets[hash]);
        for (; itr != end(buckets[hash]); itr++) {
            if (itr->first == key) {
                buckets[hash].erase(itr);
                size--;
                cout << "Deleted item\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }
    optional<string> getItem(string key) {
        if (size == 0) {
            cout << "Empty Table.\n";
            return {};
        }
        int hash = hash_function(key);
        auto itr = begin(buckets[hash]);
        for (; itr != end(buckets[hash]); itr++) {
            if (itr->first == key) {
                return itr->second;
            }
        }
        return {};
    }
};

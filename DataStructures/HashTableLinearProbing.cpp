#include <bits/stdc++.h>
using namespace std;
class HashTable {
  private:
    enum State { EMPTY, OCCUPIED, DELETED };
    static const int initCapacity = 256;
    int occupiedCount, keyCount, capacity;
    double threshold = 0.5;
    vector<pair<string, string>> table;
    vector<State> states;

    int hash_function(string key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % capacity;
        }
        return hash;
    }

    void resizeTable() {
        int oldCap = capacity;
        vector<pair<string, string>> oldTable(table);
        vector<State> oldStates(states);

        capacity *= 2;
        occupiedCount = 0;
        keyCount = 0;
        table.assign(capacity, {});
        states.assign(capacity, EMPTY);

        for (int i = 0; i < oldCap; ++i) {
            if (oldStates[i] != OCCUPIED)
                continue;
            insertItem(oldTable[i].first, oldTable[i].second);
        }
    }

  public:
    HashTable() : capacity(initCapacity), keyCount(0), occupiedCount(0) {
        table.resize(capacity, {});
        states.resize(capacity, EMPTY);
    }

    void insertItem(string key, string value) {
        int index = hash_function(key);
        int tombIndx = -1;

        while (states[index] != EMPTY) {
            if (states[index] == OCCUPIED && table[index].first == key) {
                if (tombIndx == -1) {
                    table[index].second = value;
                } else {
                    table[tombIndx] = make_pair(key, value);
                    states[tombIndx] = OCCUPIED;

                    table[index] = {};
                    states[index] = DELETED;
                }
                return;
            }
            if (states[index] == DELETED && tombIndx == -1)
                tombIndx = index;
            index = (index + 1) % capacity;
        }

        if (tombIndx != -1) {
            table[tombIndx] = make_pair(key, value);
            states[tombIndx] = OCCUPIED;
            keyCount++;
        } else {
            table[index] = make_pair(key, value);
            states[index] = OCCUPIED;
            occupiedCount++;
            keyCount++;
        }

        if ((double)occupiedCount / capacity > threshold)
            resizeTable();
    }
    optional<string> getItem(string key) {
        int index = hash_function(key);
        int initial = index;
        int tombIndx = -1;

        while (states[index] != EMPTY) {
            if (states[index] == DELETED && tombIndx == -1)
                tombIndx = index;

            if (states[index] == OCCUPIED && table[index].first == key) {
                auto kv = table[index];
                if (tombIndx != -1) {
                    table[tombIndx] = kv;
                    table[index] = {};

                    states[tombIndx] = OCCUPIED;
                    states[index] = DELETED;
                }
                return kv.second;
            }
            index = (index + 1) % capacity;
            if (index == initial)
                return {};
        }
        return {};
    }
    void eraseItem(string key) {
        int index = hash_function(key);
        int initial = index;

        while (states[index] != EMPTY) {
            if (states[index] == OCCUPIED && table[index].first == key) {
                table[index] = {};
                states[index] = DELETED;
                keyCount--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == initial)
                break;
        }
        cout << "Key doesn't exist.\n";
    }
    int getSize() { return keyCount; }
};

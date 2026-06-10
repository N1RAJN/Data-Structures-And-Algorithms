#include <bits/stdc++.h>
using namespace std;
class DSU {
    size_t size;
    vector<int> parent;
    vector<int> rank;

  public:
    DSU(int _size) : size(_size) {
        parent.resize(_size);
        rank.resize(_size, 0);
    }

    void makeSet(int i) { parent[i] = i; }

    int findSet(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = findSet(parent[i]);
    }

    void unionSet(int a, int b) {
        int i = findSet(a);
        int j = findSet(b);

        if (i != j) {
            if (rank[j] < rank[i])
                swap(j, i);
            parent[i] = j;
            if (rank[j] == rank[i])
                rank[j]++;
        }
    }
};

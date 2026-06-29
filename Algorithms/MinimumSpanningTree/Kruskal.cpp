#include <bits/stdc++.h>
using namespace std;
class DSU {
    vector<int> parent, rank;

  public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int findSet(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = findSet(parent[i]);
    }

    void unionSet(int a, int b) {
        int i = findSet(a);
        int j = findSet(b);

        if (i != j) {
            if (rank[i] < rank[j])
                swap(i, j);
            parent[j] = i;
            if (rank[i] == rank[j])
                rank[i]++;
        }
    }
};

struct Edge {
    int u, v, w;
    bool operator<(Edge const &other) { return w < other.w; }
};

int kruskal(int n, vector<Edge> &edges) {
    DSU d(n);
    int cost = 0;

    sort(edges.begin(), edges.end());

    for (Edge &e : edges) {
        if (d.findSet(e.u) != d.findSet(e.v)) {
            cost += e.w;
            d.unionSet(e.u, e.v);
        }
    }
    return cost;
}

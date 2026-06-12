#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w; // From, To, Weight
};

// Negative Cycle or not
bool bellmanFord(vector<Edge> &edges, int v, int src, vector<int> &minDist,
                 vector<int> &parent) {

    minDist.assign(v, INT_MAX);
    parent.assign(v, -1);

    minDist[src] = 0;

    // Shortest Path and Parent
    for (int i = 0; i < v; i++) {
        bool relaxed = false;
        for (Edge e : edges) {
            if (minDist[e.u] == INT_MAX)
                continue;
            int newDist = minDist[e.u] + e.w;
            int oldDist = minDist[e.v];
            if (newDist < oldDist) {
                minDist[e.v] = newDist;
                parent[e.v] = e.u;
                relaxed = true;
            }
        }
        if (!relaxed)
            break;
    }

    // Negative Cycle
    bool relaxed = false;
    for (Edge e : edges) {
        if (minDist[e.u] + e.w < minDist[e.v]) {
            relaxed = true;
            break;
        }
    }
    return relaxed;
}

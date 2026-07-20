#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w; // From, To, Weight
};

// Negative Cycle or not
vector<int> bellmanFord(vector<Edge> &edges, int v, int src,
                        vector<int> &minDist, vector<int> &parent) {
    minDist.assign(v, INT_MAX);
    parent.assign(v, -1);

    minDist[src] = 0;

    int relaxedVertex;
    for (int i = 0; i < v; i++) {
        relaxedVertex = -1;
        for (Edge e : edges) {
            if (minDist[e.u] == INT_MAX)
                continue;
            int newDist = minDist[e.u] + e.w;
            int oldDist = minDist[e.v];
            if (newDist < oldDist) {
                minDist[e.v] = newDist;
                parent[e.v] = e.u;
                relaxedVertex = e.v;
            }
        }
    }

    if (relaxedVertex == -1)
        return {};

    int cycleVertex = relaxedVertex;
    // NOTE: If there is a negative cycle, and you walk back v times, you must
    // be eventually enter (and get stuck) inside the cycle
    for (int i = 0; i < v; ++i)
        cycleVertex = parent[cycleVertex];

    int curr = cycleVertex;
    vector<int> cycle;
    do {
        cycle.push_back(curr);
        curr = parent[curr];
    } while (curr != cycleVertex);

    reverse(cycle.begin(), cycle.end());
    return cycle;
}

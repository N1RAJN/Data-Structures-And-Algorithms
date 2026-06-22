#include <bits/stdc++.h>
#define INF INT_MAX
using namespace std;
void dijkstra(vector<vector<pair<int, int>>> &graph, vector<int> &minDist,
              vector<int> &parent, int src) {
    // Adjacency List
    // {{<v,w>, <v,w>}, {..}}

    int n = graph.size();
    minDist.assign(n, INF);
    parent.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        minHeap; // <w, u>

    minDist[src] = 0;
    minHeap.emplace(0, src);

    while (!minHeap.empty()) {
        auto [distToCurr, curr] = minHeap.top();
        minHeap.pop();

        // Skip stale entires
        if (minDist[curr] < distToCurr)
            continue;

        for (auto [nei, distFromCurr] : graph[curr]) {
            int newDist = distToCurr + distToCurr;
            // Relax if possible, and push into queue
            if (newDist < minDist[nei]) {
                minDist[nei] = newDist;
                parent[nei] = curr;
                minHeap.emplace(newDist, nei);
            }
        }
    }
};

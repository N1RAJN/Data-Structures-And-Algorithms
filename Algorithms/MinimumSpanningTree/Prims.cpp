#include <bits/stdc++.h>
#include <climits>
using namespace std;
// Dense Graph
struct Edge {
    int to, w = INT_MAX;
};
void primsDense(vector<vector<int>> &adjMatrix, int &minCost) {
    int n = adjMatrix.size();
    vector<Edge> minEdges(n);
    vector<bool> selected(n, false);
    minCost = 0;

    // Choose a vertex arbritrarily
    minEdges[0].w = 0;

    for (int i = 0; i < n; i++) { // Until we have n - 1 edges in the MST
        int minVertex = -1;
        for (int j = 0; j < n; j++) { // Choose the minimum weight edge
            if (!selected[j] &&
                (minVertex == -1 || minEdges[j].w < minEdges[minVertex].w))
                minVertex = j;
        }

        if (minEdges[minVertex].w == INT_MAX) {
            printf("Disconnected graph. No MST\n");
            exit(1);
        }

        selected[minVertex] = true;
        minCost += minEdges[minVertex].w;

        // The newly selected vertex could have an edge with lower cost with
        // some unselected vertex's previous minEdge
        for (int to = 0; to < n; to++) {
            if (!selected[to] && adjMatrix[minVertex][to] < minEdges[to].w) {
                minEdges[to] = {minVertex, adjMatrix[minVertex][to]};
            }
        }
    }
}

// Sparse Graph
void primsSparse(vector<vector<pair<int, int>>> &adjList, int &minCost) {
    int n = adjList.size();
    minCost = 0;
    int selectedCount = 0;
    vector<bool> selected(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        minHeap; // {weight, vertex}

    minHeap.emplace(0, 0);

    while (selectedCount < n) {
        if (minHeap.empty()) {
            printf("NO MST.\n");
            exit(1);
        }

        auto [w, v] = minHeap.top();
        minHeap.pop();

        if (selected[v])
            continue;

        minCost += w;
        selected[v] = true;
        selectedCount++;

        for (auto &[to, weight] : adjList[v]) {
            if (!selected[to])
                minHeap.emplace(weight, to);
        }
    }
}

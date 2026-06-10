#include <bits/stdc++.h>
#include <climits>
#include <queue>
using namespace std;
using weightedAdjacencyList =
    vector<vector<pair<int, int>>>; // [[{vertex, weight}, {vertex, weight}],
                                    // [...], [..]]
using verticesList = vector<int>;

verticesList dijkstra(const weightedAdjacencyList &graph, int source,
                      int sink) {
    int vertexCount = graph.size();

    vector<int> distances(vertexCount, INT_MAX);
    verticesList parent(vertexCount, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        minHeap; // {distance, vertex}

    distances[source] = 0;
    minHeap.emplace(0, source);

    while (!minHeap.empty()) {
        auto [currDist, currVertex] = minHeap.top();
        minHeap.pop();
        if (currDist > distances[currVertex])
            continue;
        if (currVertex == sink)
            break;
        for (auto [vertex, weight] : graph[currVertex]) {
            int distFromCurr = weight + currDist;
            if (distFromCurr < distances[vertex]) {
                distances[vertex] = distFromCurr;
                parent[vertex] = currVertex;
                minHeap.emplace(distFromCurr, vertex);
            }
        }
    }
    verticesList path;
    if (parent[sink] == -1 && sink != source)
        return path;
    int curr = sink;
    while (parent[curr] != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());
    return path;
}

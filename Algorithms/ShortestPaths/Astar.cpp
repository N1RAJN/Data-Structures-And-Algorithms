#include <bits/stdc++.h>
#define INF 1e5
using namespace std;
int heuristic(int node, int goal) {
    // Some estimate of the cheapest cost to the goal node
    return 0;
}
void Astar(vector<vector<pair<int, int>>> &graph, vector<int> &minDist,
           vector<int> &parent, int src, int goal) {

    int n = graph.size();
    minDist.assign(n, INF);
    parent.assign(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        minHeap;

    minDist[src] = 0;
    minHeap.emplace(heuristic(src, goal), src);

    while (!minHeap.empty()) {
        auto [fScore, curr] = minHeap.top();
        minHeap.pop();

        if (curr == goal)
            break;

        if (minDist[curr] < fScore - heuristic(curr, goal))
            continue;

        for (auto [nei, distFromCurr] : graph[curr]) {
            int newDist = minDist[curr] + distFromCurr;
            if (newDist < minDist[nei]) {
                minDist[nei] = newDist;
                parent[nei] = curr;
                minHeap.emplace(newDist + heuristic(nei, goal), nei);
            }
        }
    }
}

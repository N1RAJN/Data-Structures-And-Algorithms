// Shortest Path Faster Algorithm
// Queue optimization on Bellman Ford.
#include <bits/stdc++.h>
using namespace std;

bool SPFA(vector<vector<pair<int, int>>> &adjList, int src,
          vector<int> &minDist, vector<int> &parent) {
    int n = adjList.size();
    vector<bool> inQueue(n, false);
    vector<int> relaxCount(n, 0);

    minDist.assign(n, INT_MAX);
    parent.assign(n, -1);

    minDist[src] = 0;
    queue<int> q;
    q.push(src);
    inQueue[src] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        inQueue[v] = false;

        if (minDist[v] == INT_MAX)
            continue;

        for (auto &[u, w] : adjList[v]) {
            int newDist = minDist[v] + w;

            if (newDist < minDist[u]) {
                minDist[u] = newDist;
                parent[u] = v;
                if (!inQueue[u]) {
                    q.push(u);
                    inQueue[u] = true;

                    relaxCount[u]++;
                    if (relaxCount[u] > n - 1) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

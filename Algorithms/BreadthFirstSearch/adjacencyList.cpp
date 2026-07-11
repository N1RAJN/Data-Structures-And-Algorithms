#include <bits/stdc++.h>
using namespace std;
void bfs(const vector<vector<int>> &adj, vector<int> &parent, vector<int> &dist,
         int src) {
    // NOTE: Parent => which node was added to the queue by which node
    // Dist => distance of each node from the source node

    int n = adj.size();
    parent.assign(n, -1);
    dist.assign(n, -1);

    queue<int> q;
    parent[src] = src;
    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

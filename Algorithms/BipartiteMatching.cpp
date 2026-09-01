#include <bits/stdc++.h>
using namespace std;

bool bipartite_match(vector<vector<int>> &adj, vector<int> &colour) {
    int n = adj.size();
    colour.assign(n, -1);
    bool is_bipartite = true;

    for (int st = 0; st < n; ++st) {
        // Start BFS if not already visited
        if (colour[st] != -1)
            continue;
        queue<int> q;
        q.push(st);
        colour[st] = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (colour[u] == -1) {
                    colour[u] = colour[v] ^ 1;
                    q.push(v);
                } else {
                    // Visited neighbors should be on the other side
                    is_bipartite &= (colour[u] != colour[v]);
                }
            }
        }
    }
    return is_bipartite;
}

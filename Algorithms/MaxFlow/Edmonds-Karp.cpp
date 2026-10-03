#include <bits/stdc++.h>
using namespace std;
const int INF = 1e5;

int n;
vector<vector<int>> capacity, adj;

int bfs(int s, int t, vector<int> parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;

    q.push({s, INF});
    while (q.size()) {
        auto [u, f] = q.front();
        q.pop();

        for (int v : adj[u]) {
            // If not visited and has positive capacity
            if (parent[u] == -1 && capacity[u][v]) {
                parent[v] = u;
                int new_f = min(f, capacity[u][v]);
                if (v == t)
                    return new_f;
                q.push({v, new_f});
            }
        }
    }
    return 0;
}

int Edmonds_Karp(int s, int t) {
    int max_flow = 0;
    vector<int> parent(n);

    int net_flow = 0;
    while ((net_flow = bfs(s, t, parent))) {
        max_flow += net_flow;
        int curr = t;
        while (curr != s) {
            int prev = parent[curr];
            // Capacity will never go negative because initially all the
            // capacities are non-negative
            // For a capacity of an edge to get negative, it has to lie on an
            // augmenting and the min_residual of that path must be greater than
            // residual of the edge, which is not possible
            capacity[prev][curr] -= net_flow;
            capacity[curr][prev] += net_flow;
            curr = prev;
        }
    }
    return max_flow;
}

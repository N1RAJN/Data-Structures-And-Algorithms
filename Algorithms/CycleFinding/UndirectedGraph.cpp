#include <bits/stdc++.h>
using namespace std;
// NOTE: In an undirected graph, once you visit a vertex and explore all its
// edges, we've seen everything reachable from that vertex
// Hence, no other DFS tree can reach that vertex again because reachability is
// symmetric.

vector<bool> visited;
vector<int> parent;
int cycle_start; // Node at which cycle starts.
int cycle_end;   // Last node in the cycle excluding the start

bool dfs(vector<vector<int>> &adj, int u, int par) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (v == par)
            continue;
        if (visited[v]) {
            cycle_end = u;
            cycle_start = v;
            return true;
        }
        parent[v] = u;
        if (dfs(adj, v, u))
            return true;
    }
    return false;
}
void find_cycle(vector<vector<int>> &adj) {
    int n = adj.size();
    parent.assign(n, -1);
    visited.assign(n, 0);
    cycle_start = -1;

    for (int u = 0; u < n; ++u)
        if (!visited[u] && dfs(adj, u, parent[u]))
            break;

    if (cycle_start == -1) {
        cout << "NO Cycle\n";
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(cycle_start);

        cout << "Cycle Found\n";
        for (int v : cycle)
            cout << v << " ";
        cout << "\n";
    }
}

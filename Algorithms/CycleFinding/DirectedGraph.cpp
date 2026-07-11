#include <bits/stdc++.h>
using namespace std;
// NOTE: Just tracking visisted or not is not enough to detect cycle
// Because a cycle only exist when we try to visit a node that we're already
// visting and hasn't been full processed yet.

// NOTE: Back-edge to a black node (visited) means it's a cross edge
// Back-edge to a grey node (visiting) means there's a cycle

vector<int> colour; // 0 -> unvisited, 1 -> visiting, 2 -> visited
vector<int> parent;
int cycle_start; // Node at which cycle starts.
int cycle_end;   // Last node in the cycle excluding the start

bool dfs(vector<vector<int>> &adj, int u) {
    colour[u] = 1;
    for (int v : adj[u]) {
        if (colour[v] == 1) {
            cycle_end = u;
            cycle_start = v;

            return true;
        } else if (colour[v] == 0) {
            parent[v] = u;

            if (dfs(adj, v))
                return true;
        }
    }
    colour[u] = 2;
    return false;
}
void find_cycle(vector<vector<int>> &adj) {
    int n = adj.size();
    parent.assign(n, -1);
    colour.assign(n, 0);
    cycle_start = -1;

    for (int u = 0; u < n; ++u)
        if (colour[u] == 0 && dfs(adj, u))
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

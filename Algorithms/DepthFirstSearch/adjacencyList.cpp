#include <bits/stdc++.h>
using namespace std;

vector<int> parent, time_in, time_out, colour;
int timer = 0;

// NOTE: Parent => Which node added a node to the dfs tree
// time_in => When was the node added to the dfs tree
// time_out => When did the node was marked visited
// colour => Current state of a node:
//          0 -> unvisited (hasn't been seen by the dfs)
//          1 -> visiting (in the recursion stack)
//          2 -> visited (fully processed)

void dfs(vector<vector<int>> &adj, int u) {
    colour[u] = 1;
    time_in[u] = timer++;

    for (int v : adj[u]) {
        if (colour[v] == 0) {
            parent[v] = u;
            dfs(adj, v);
        }
    }

    time_out[u] = timer++;
    colour[u] = 2;
}

void traverse(vector<vector<int>> &adj) {
    int n = adj.size();
    parent.assign(n, -1);
    time_in.assign(n, -1);
    time_out.assign(n, -1);
    colour.assign(n, 0);

    timer = 0;
    for (int u = 0; u < n; ++u)
        if (colour[u] == 0)
            dfs(adj, u);
}

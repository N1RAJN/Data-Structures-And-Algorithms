#include <bits/stdc++.h>
using namespace std;

void dfs(int v, vector<vector<int>> &adjList, vector<bool> &visited,
         vector<int> &output) {
    visited[v] = true;
    for (int &u : adjList[v]) {
        if (!visited[u])
            dfs(u, adjList, visited, output);
    }
    output.push_back(v);
}

void kosaraju(vector<vector<int>> &adjList, vector<vector<int>> &components,
              vector<vector<int>> &condensedAdjList) {
    int n = adjList.size();

    vector<bool> visited(n, false);
    components.clear(), condensedAdjList.clear();

    vector<int> order;
    // DFS 1
    for (int v = 0; v < n; v++)
        if (!visited[v])
            dfs(v, adjList, visited, order);
    visited.assign(n, false);
    reverse(order.begin(), order.end());

    // Transpose of Graph
    vector<vector<int>> adjRev(n);
    for (int v = 0; v < n; v++)
        for (int u : adjList[v])
            adjRev[u].push_back(v);

    vector<int> roots(n, 0); // Root vertex of SCC
    // DFS 2
    for (int &v : order) {
        if (!visited[v]) {
            vector<int> component;
            dfs(v, adjRev, visited, component);
            components.push_back(component);
            int root = *(component.begin());
            for (int u : component)
                roots[u] = root;
        }
    }
    unordered_map<int, int> sccIndex;
    for (int i = 0; i < components.size(); ++i)
        sccIndex[components[i][0]] = i;

    // Condense the graph
    condensedAdjList.assign(components.size(), {});
    for (int v = 0; v < n; v++)
        for (int &u : adjList[v]) {
            int ru = roots[u], rv = roots[v];
            if (ru != rv)
                condensedAdjList[sccIndex[rv]].push_back(sccIndex[ru]);
        }
}

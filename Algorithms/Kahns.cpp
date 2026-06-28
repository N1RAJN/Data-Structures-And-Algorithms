// Topological Sort
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

vector<int> kahns(vector<vector<int>> &adjList) {
    int n = adjList.size();
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int &nei : adjList[i])
            indegree[nei]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> result;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        result.push_back(v);
        for (int &nei : adjList[v]) {
            indegree[nei]--;
            if (indegree[nei] == 0)
                q.push(nei);
        }
    }
    return result;
}

// using dfs
void dfs(vector<vector<int>> &adjList, int v, vector<int> &result,
         vector<bool> &visited) {
    visited[v] = true;
    for (int &nei : adjList[v]) {
        dfs(adjList, nei, result, visited);
    }
    result.push_back(v);
}

vector<int> topologicalSort(vector<vector<int>> &adjList) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<int> result;

    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(adjList, i, result, visited);
    }
    reverse(result.begin(), result.end());
    return result;
}

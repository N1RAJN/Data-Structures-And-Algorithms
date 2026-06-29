#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
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

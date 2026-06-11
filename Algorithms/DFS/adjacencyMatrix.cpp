#include <bits/stdc++.h>
using namespace std;
bool dfs(const vector<vector<int>> &graphMatrix, vector<bool> &seen,
         vector<int> &result, int curr, int sink) {

    if (curr == sink) {
        return true;
    }
    for (int i = 0; i < graphMatrix.size(); ++i) {
        if (!graphMatrix[curr][i] || seen[i])
            continue;
        seen[i] = true;
        result.push_back(i);
        if (dfs(graphMatrix, seen, result, i, sink))
            return true;
        result.pop_back();
    }
    return false;
}
vector<int> DFSadjacencyMatrix(const vector<vector<int>> &graphMatrix,
                               int source, int sink) {

    vector<bool> seen(graphMatrix.size(), false);
    vector<int> result = {};
    result.push_back(source);
    seen[source] = true;
    dfs(graphMatrix, seen, result, source, sink);
    return result;
}

#include <bits/stdc++.h>
using namespace std;
bool dfs(const vector<vector<int>> &graphList, vector<int> &result,
         vector<bool> &seen, int curr, int sink) {
    result.push_back(curr);
    seen[curr] = true;
    if (curr == sink) {
        return true;
    }
    vector<int> edges = graphList[curr];
    for (int i = 0; i < edges.size(); ++i) {
        if (!seen[edges[i]] && dfs(graphList, result, seen, edges[i], sink))
            return true;
    }
    result.pop_back();
    return false;
}
vector<int> DFSadjacencyList(const vector<vector<int>> &graphList, int source,
                             int sink) {
    vector<bool> seen(graphList.size(), false);
    vector<int> result = {};
    dfs(graphList, result, seen, source, sink);
    return result;
}

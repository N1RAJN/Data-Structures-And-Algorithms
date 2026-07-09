#include <bits/stdc++.h>
using namespace std;

int findStartNode(int n, const vector<int> &inDegrees,
                  const vector<int> &outDegrees) {

    // NOTE: In case of existence of cycle, any node can be taken as the start??
    // Node with one extra outgoing edge must be the start of path.
    int start = 0;
    for (int v = 0; v < n; ++v) {
        if (outDegrees[v] - inDegrees[v] == 1)
            return v;
        if (outDegrees[v] > 0)
            start = v;
    }
    return start;
}

bool hasEulerPath(int n, const vector<int> &inDegrees,
                  const vector<int> &outDegrees, int edgeCount) {
    if (edgeCount == 0)
        return false;

    int startNodes = 0, endNodes = 0;
    for (int v = 0; v < n; ++v) {
        // NOTE: For cycle, each node must have equal number of incoming and
        // outgoing edges (inorder to not get "stuck" at that vertex)
        int diff = outDegrees[v] - inDegrees[v];
        int absDiff = diff < 0 ? -diff : diff;

        // NOTE: If a cycle doesn't exist, a path might still exist
        // if and only if
        // 1.There are exactly one vertex with one more incoming edge than
        // outgoing edge and exactly one vertex with vice versa
        // 2.These "extra" two vertices must the start (the one with 1 (only)
        // extra outgoing edge) and the end (the one with 1 (only) extra
        // incoming edge)
        if (absDiff > 1)
            return false;
        else if (diff == 1)
            startNodes++;
        else if (diff == -1)
            endNodes++;
    }
    // NOTE: Cycle exists
    if (startNodes == 0 && endNodes == 0)
        // NOTE: Every vertex have equal incoming  and outgoing edge
        return true;

    // NOTE: Path existence
    // Exactly one vertex has one extra outgoing and
    // one vertex has one extra incoming
    return (startNodes == 1 && endNodes == 1);
}

void dfs(vector<vector<int>> &adjList, vector<int> &outDegree,
         vector<int> &path, int n, int v) {
    stack<int> st;
    st.push(v);
    while (!st.empty()) {
        int u = st.top();
        if (outDegree[u] != 0) {
            outDegree[u]--;
            // Use the size of outdegree array to choose the next edge
            st.push(adjList[u][outDegree[u]]);
        } else {
            path.push_back(u);
            st.pop();
        }
    }
}

vector<int> heirholzer(vector<vector<int>> &adjList) {
    int n = adjList.size();
    int edgeCount = 0;

    vector<int> inDegree(n, 0);
    vector<int> outDegree(n, 0);
    vector<int> path;

    for (int v = 0; v < n; ++v) {
        for (int u : adjList[v]) {
            inDegree[u]++;
            outDegree[v]++;
            edgeCount++;
        }
    }

    if (!hasEulerPath(n, inDegree, outDegree, edgeCount))
        return path;

    int start = findStartNode(n, inDegree, outDegree);
    dfs(adjList, outDegree, path, n, start);

    // Disconnected graph
    if (path.size() != edgeCount + 1)
        return {};
    reverse(path.begin(), path.end());
    return path;
}

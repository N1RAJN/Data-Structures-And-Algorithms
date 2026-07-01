#include <bits/stdc++.h>
using namespace std;

int findStartNode(int n, const vector<int> &inDegrees,
                  const vector<int> &outDegrees) {
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
        int diff = outDegrees[v] - inDegrees[v];
        int absDiff = diff < 0 ? -diff : diff;
        if (absDiff > 1)
            return false;
        else if (diff == 1)
            startNodes++;
        else if (diff == -1)
            endNodes++;
    }
    return (startNodes == 0 && endNodes == 0) ||
           (startNodes == 1 && endNodes == 1);
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

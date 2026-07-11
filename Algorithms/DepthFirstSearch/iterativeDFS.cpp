#include <bits/stdc++.h>
using namespace std;

vector<int> dfs(const vector<vector<int>> &adjList, int src) {
    int n = adjList.size();
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    stack<int> st;
    st.push(src);
    visited[src] = true;
    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
                parent[v] = u;
            }
        }
    }
    return parent;
}

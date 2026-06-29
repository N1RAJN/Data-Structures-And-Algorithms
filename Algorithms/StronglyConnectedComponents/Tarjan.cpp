#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int timer;
stack<int> st;
vector<int> roots;
vector<int> t_in;
vector<int> t_low;
void dfs(int v, vector<vector<int>> &adjList, vector<vector<int>> &components) {

    t_in[v] = t_low[v] = timer++;
    st.push(v);

    // Visit all neighbors
    for (auto &u : adjList[v]) {
        if (t_in[u] == -1) // Unvisited vertex
            dfs(u, adjList, components);
        if (roots[u] == -1) // Unclaimed vertex
            t_low[v] = min(t_low[u], t_low[v]);
    }

    if (t_in[v] == t_low[v]) {
        vector<int> component;
        for (;;) {
            int u = st.top();
            st.pop();

            component.push_back(u);
            roots[u] = v;
            if (u == v)
                break;
        }
        components.push_back(component);
    }
}

void tarjan(vector<vector<int>> &adjList, vector<vector<int>> &components,
            vector<vector<int>> &condensedAdjList) {
    components.clear();
    condensedAdjList.clear();

    int n = adjList.size();
    timer = 0;
    roots.assign(n, -1);
    t_in.assign(n, -1);
    t_low.assign(n, -1);

    for (int v = 0; v < n; ++v)
        if (t_in[v] == -1)
            dfs(v, adjList, components);

    unordered_map<int, int> sccIndex;
    for (int i = 0; i < components.size(); ++i)
        sccIndex[components[i].back()] = i;

    // Condense the graph
    set<pair<int, int>> seen;
    condensedAdjList.assign(components.size(), {});
    for (int v = 0; v < n; v++) {
        for (int &u : adjList[v]) {
            int ru = roots[u], rv = roots[v];
            if (ru != rv && !seen.count({roots[u], roots[v]})) {
                seen.insert({roots[u], roots[v]});
                condensedAdjList[sccIndex[rv]].push_back(sccIndex[ru]);
            }
        }
    }
}

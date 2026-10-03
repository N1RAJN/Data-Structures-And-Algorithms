#include <bits/stdc++.h>
using namespace std;
#define INF 1e5

struct Edge {
    int to, cap, flow;
};
vector<Edge> edges;
vector<vector<int>> graph; // Stores list of edges for every node

void add_edge(int from, int to, int cap) {
    // NOTE: Since forward edge and reverse edges are added in tandem, the last
    // bit of their indices differ by one
    // Forward edge at index i
    // Reverse edge at index i ^ 1.

    // Since appended to the end, use size of the edge list as
    // index
    graph[from].push_back(edges.size());
    edges.push_back({to, cap, 0});

    graph[to].push_back(edges.size());
    edges.push_back({from, 0, 0}); // reverse edge with 0 capacity
}

int visit_token = 0;
vector<int> visited;

int dfs(int node, int t, int flow) {
    if (node == t)
        return flow;

    visited[node] = visit_token;
    for (int v : graph[node]) {
        int rCap = edges[v].cap - edges[v].flow;
        if (rCap > 0 && visited[edges[v].to] != visit_token) {
            int f = dfs(edges[v].to, t, min(rCap, flow));
            if (f > 0) {
                edges[v].flow += f;
                edges[v ^ 1].flow -= f;
                return f;
            }
        }
    }
    return 0;
}

int FordFolkerson(int source, int target) {
    int n = graph.size();
    int maxFlow = 0, f = 0;
    visited.assign(n, visit_token);

    while (true) {
        visit_token++;
        f = dfs(source, target, INF);
        if (f == 0)
            break;
        maxFlow += f;
    }

    return maxFlow;
}

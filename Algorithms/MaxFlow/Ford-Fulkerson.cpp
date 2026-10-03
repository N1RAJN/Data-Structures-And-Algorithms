#include <bits/stdc++.h>
using namespace std;
#define INF 1e5
const int mxN = 1000;

int visit_token = 0;
vector<int> visited;

int dfs(int rGraph[mxN][mxN], int n, int node, int t, int flow) {
    if (node == t)
        return flow;

    visited[node] = visit_token;
    for (int i = 0; i < n; ++i) {
        if (rGraph[node][i] > 0 && visited[i] != visit_token) {
            int bottleneck = dfs(rGraph, n, i, t, min(rGraph[node][i], flow));
            if (bottleneck > 0) {
                rGraph[node][i] += bottleneck;
                rGraph[i][node] -= bottleneck;
                return bottleneck;
            }
        }
    }
    return 0;
}

int FordFolkerson(int graph[mxN][mxN], int n, int source, int target) {
    int maxFlow = 0, f = 0;
    int rGraph[mxN][mxN];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            rGraph[i][j] = graph[i][j];
    }

    visited.assign(n, visit_token);
    while (true) {
        visit_token++;
        f = dfs(rGraph, n, source, target, INF);
        if (f == 0)
            break;
        maxFlow += f;
    }

    return maxFlow;
}

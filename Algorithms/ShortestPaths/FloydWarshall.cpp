#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
void floydWarshall(const vector<vector<int>> &adjMatrix,
                   vector<vector<int>> &dist, vector<vector<int>> &next) {
    int n = adjMatrix.size();
    dist.assign(n, vector<int>(n, INF));
    next.assign(n, vector<int>(n, -1));

    // Initialize shortest dist
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != INF)
                next[i][j] = j;
            dist[i][j] = adjMatrix[i][j];
        }
    }

    // Bottom-up shortest distance matrix
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

// Path reconstruction
vector<int> reconstructPath(vector<vector<int>> &next, int source, int dest) {
    if (next[source][dest] == -1)
        return {};
    vector<int> path;
    int curr = source;
    while (curr != dest) {
        path.push_back(curr);
        curr = next[curr][dest];
        if (curr == -1)
            return {};
    }
    path.push_back(dest);
    return path;
}

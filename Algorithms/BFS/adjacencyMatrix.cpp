#include <bits/stdc++.h>
using namespace std;
vector<int> BFSadjacencyMatrix(const vector<vector<int>> &graphMatrix,
                               int source, int sink) {
    int n = graphMatrix.size();
    vector<bool> seen(n, false); // To avoid duplicate visits
    vector<int> prev(n, -1);     // For path  reconstruction
    queue<int> vertices;
    vector<int> result = {};

    seen[source] = true;
    int curr = source;
    vertices.push(curr);

    do {
        curr = vertices.front();
        vertices.pop();
        if (curr == sink)
            break;
        vector<int> neighbors = graphMatrix[curr];
        for (int i = 0; i < n; ++i) {
            if (!neighbors[i] || seen[i])
                continue;
            seen[i] = true;
            prev[i] = curr;
            vertices.push(i);
        }

    } while (vertices.size());

    if (prev[sink] == -1)
        return result;
    curr = sink;
    while (prev[curr] != -1) {
        result.push_back(curr);
        curr = prev[curr];
    }
    result.push_back(source);
    reverse(result.begin(), result.end());
    return result;
}

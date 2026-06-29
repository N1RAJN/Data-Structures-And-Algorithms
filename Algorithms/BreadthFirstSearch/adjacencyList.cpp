#include <bits/stdc++.h>
using namespace std;
vector<int> BFSadjacencyList(const vector<vector<int>> &graphList, int source,
                             int sink) {
    int v = graphList.size();
    vector<bool> seen(v, false);
    vector<int> prev(v, -1);
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
        vector<int> neighbors = graphList[curr];
        for (int i = 0; i < neighbors.size(); ++i) {
            int vertex = neighbors[i];
            if (seen[vertex])
                continue;
            seen[vertex] = true;
            prev[vertex] = curr;
            vertices.push(vertex);
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

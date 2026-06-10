#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
using namespace std;
using verticesList = vector<int>;
using adjacencyList = vector<verticesList>;
using weightedAdjacencyList = vector<vector<pair<int, int>>>;
using adjacencyMatrix = vector<vector<int>>;

verticesList BFSadjacencyMatrix(const adjacencyMatrix &graphMatrix, int source,
                                int sink) {
    int matrixSize = graphMatrix.size();
    vector<bool> seen(matrixSize, false);
    verticesList prev(matrixSize, -1);
    queue<int> vertices;
    verticesList result = {};

    seen[source] = true;
    int curr = source;
    vertices.push(curr);

    do {
        curr = vertices.front();
        vertices.pop();
        if (curr == sink)
            break;
        verticesList currConnections = graphMatrix[curr];
        for (int i = 0; i < matrixSize; ++i) {
            if (!currConnections[i] || seen[i])
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

bool dfs(const adjacencyMatrix &graphMatrix, vector<bool> &seen,
         verticesList &result, int curr, int sink) {
    if (curr == sink) {
        return true;
    }
    for (int i = 0; i < graphMatrix.size(); ++i) {
        if (!graphMatrix[curr][i] || seen[i])
            continue;
        seen[i] = true;
        result.push_back(i);
        if (dfs(graphMatrix, seen, result, i, sink))
            return true;
        result.pop_back();
    }
    return false;
}
verticesList DFSadjacencyMatrix(const adjacencyMatrix &graphMatrix, int source,
                                int sink) {
    vector<bool> seen(graphMatrix.size(), false);
    verticesList result = {};
    result.push_back(source);
    seen[source] = true;
    dfs(graphMatrix, seen, result, source, sink);
    return result;
}

verticesList BFSadjacencyList(const adjacencyList &graphList, int source,
                              int sink) {
    int vertexCount = graphList.size();
    vector<bool> seen(vertexCount, false);
    verticesList prev(vertexCount, -1);
    queue<int> vertices;
    verticesList result = {};

    seen[source] = true;
    int curr = source;
    vertices.push(curr);

    do {
        curr = vertices.front();
        vertices.pop();
        if (curr == sink)
            break;
        verticesList currConnections = graphList[curr];
        for (int i = 0; i < currConnections.size(); ++i) {
            int vertex = currConnections[i];
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
bool dfsList(const adjacencyList &graphList, verticesList &result,
             vector<bool> &seen, int curr, int sink) {
    result.push_back(curr);
    seen[curr] = true;
    if (curr == sink) {
        return true;
    }
    verticesList edges = graphList[curr];
    for (int i = 0; i < edges.size(); ++i) {
        if (!seen[edges[i]] && dfsList(graphList, result, seen, edges[i], sink))
            return true;
    }
    result.pop_back();
    return false;
}
verticesList DFSadjacencyList(const adjacencyList &graphList, int source,
                              int sink) {
    vector<bool> seen(graphList.size(), false);
    verticesList result = {};
    dfsList(graphList, result, seen, source, sink);
    return result;
}
int main() {
    adjacencyMatrix graph = {{0, 0, 1, 1, 0, 1}, {0, 0, 0, 0, 0, 1},
                             {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0},
                             {1, 0, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0}};
    adjacencyList graphList = {{2, 3, 5}, {5}, {}, {}, {0}, {3, 4}};
    int source = 1;
    int sink = 2;
    verticesList result = DFSadjacencyList(graphList, source, sink);
    for (int v : result) {
        cout << v << " -> ";
    }
    cout << "\n";
    return 0;
}

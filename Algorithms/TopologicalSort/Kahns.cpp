#include <bits/stdc++.h>
using namespace std;

vector<int> kahns(vector<vector<int>> &adjList) {
    int n = adjList.size();
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int &nei : adjList[i])
            indegree[nei]++;
    }

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> result;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        result.push_back(v);
        for (int &nei : adjList[v]) {
            indegree[nei]--;
            if (indegree[nei] == 0)
                q.push(nei);
        }
    }
    return result;
}

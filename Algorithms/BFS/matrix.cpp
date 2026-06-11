#include <bits/stdc++.h>
using namespace std;

int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void bfs(vector<vector<int>> &matrix, vector<vector<bool>> &seen) {
    // Assuming at least 1 x 1
    const int ROW = matrix.size();
    const int COL = matrix[0].size();

    int r = 0, c = 0;
    queue<pair<int, int>> q;
    q.emplace(r, c);
    seen[r][c] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        cout << matrix[r][c];

        for (auto [dr, dc] : dirs) {
            int nr = r + dr;
            int nc = c + dc;
            if (nr >= 0 && nc >= 0 && nr < ROW && nc < COL && !seen[nr][nc]) {
                seen[nr][nc] = true;
                q.emplace(nr, nc);
            }
        }
    }
}

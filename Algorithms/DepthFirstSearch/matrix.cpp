#include <bits/stdc++.h>
using namespace std;

int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void dfs(vector<vector<int>> &matrix, vector<vector<bool>> &seen, int r, int c,
         int ROW, int COL) {
    cout << matrix[r][c];
    seen[r][c] = true;
    for (auto [dr, dc] : dirs) {
        int nr = r + dr;
        int nc = c + dc;
        if (nr >= 0 && nc >= 0 && nr < ROW && nc < COL && !seen[nr][nc]) {
            dfs(matrix, seen, nr, nc, ROW, COL);
        }
    }
}

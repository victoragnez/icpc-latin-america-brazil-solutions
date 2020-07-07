#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 111;
int n, m, grid[maxn][maxn], vis[maxn][maxn];

void dfs(int x, int y) {
  if (vis[x][y]) return;
  vis[x][y] = true;
  static constexpr int mx[] = {1, -1, 0 ,0}, my[] = {0, 0, 1, -1};
  for (int k = 0; k < 4; k++) {
    int px = x + mx[k], py = y + my[k];
    if (grid[px][py] == grid[x][y]) dfs(px, py);
  }
}

int main() {
  int ans = 1;
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n + 2; i++) {
    for (int j = 1; j < m + 2; j++) {
      if (i <= n && j <= m) scanf("%d", &grid[i][j]);
      auto check = [&](int dx, int dy, bool snd) {
        int l1 = grid[i][j], r1 = grid[i + dx][j + dy];
        int l2 = grid[i - 1 - dx][j - 1 - dy], r2 = grid[i - 1][j - 1];
        if (snd) swap(l1, r1), swap(l2, r2);
        if (l1 < r1 && (r2 <= l2 || r2 <= l1 || r1 <= l2)) ans++;
      };
      check(0, -1, false);
      check(0, -1, true);
      check(-1, 0, false);
      check(-1, 0, true);
    }
  }
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < m + 1; j++) {
      if (!vis[i][j]) {
        ans++;
        dfs(i, j);
      }
    }
  }
  printf("%d\n", ans);
}

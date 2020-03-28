#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e5 + 10;
int n, ans, depth[MAXN], ord[MAXN], q_count[MAXN];
bool is_s[MAXN];
vector<int> adj[MAXN];

void dfs(int u, int p) {
  for (int v : adj[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u;
    scanf("%d", &u);
    u--;
    adj[u].push_back(i);
    adj[i].push_back(u);
  }
  dfs(0, 0);
  iota(ord, ord + n, 0);
  sort(ord + 1, ord + n, [](int i, int j) { return depth[i] > depth[j]; });
  for (int i = 1; i < n; i++) {
    int u = ord[i], p = -1;
    bool has_s = false;
    int sz = (int) adj[u].size() - 1 - q_count[u];
    for (int v : adj[u]) {
      if (depth[v] < depth[u]) {
        p = v;
        continue;
      }
      if (is_s[v]) has_s = true;
    }
    if (has_s && sz > 2) {
      ans++;
      q_count[p]++;
    } else if (sz > 1) is_s[u] = true;
  }
  printf("%d\n", ans);
}

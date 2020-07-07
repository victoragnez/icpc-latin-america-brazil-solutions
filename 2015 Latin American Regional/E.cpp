#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 222;
int vet[maxn], vis[maxn];
vector<int> adj[maxn];

void dfs(int v, int& val, int& sz, int s) {
  if (vis[v]) return;
  val += vet[v];
  vis[v] = true;
  sz += s;
  for (int u : adj[v]) dfs(u, val, sz, -s);
}

int main() {
  int a, b, e, p;
  scanf("%d%d%d%d", &a, &b, &e, &p);
  for (int i = 0; i < a + b; i++) scanf("%d", &vet[i]);
  while (e--) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    v += a;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<pair<int, int> > ccs;
  for (int i = 0; i < a + b; i++) {
    if (!vis[i]) {
      int sz = 0, val = 0;
      dfs(i, val, sz, (i < a) ? -1 : 1);
      ccs.emplace_back(sz, val);
    }
  }
  int n = (int) ccs.size();
  vector<vector<int> > dp(n + 1, vector<int>(p + 1, 0));
  auto solve = [&]() {
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j <= p; j++) {
        dp[i][j] = dp[i + 1][j];
        if (ccs[i].second <= j) {
          dp[i][j] = max(dp[i][j], dp[i + 1][j - ccs[i].second] + ccs[i].first);
        }
      }
    }
    return dp[0][p];
  };
  int ans1 = solve();
  for (int i = 0; i < (int) ccs.size(); i++) ccs[i].first *= -1;
  int ans2 = solve();
  printf("%d %d\n", ans1 + a, ans2 + b);
}

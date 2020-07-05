#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4 + 10;
constexpr int inf = 0x3f3f3f3f;

int n, m, dist[maxn][2];
vector<pair<int, int> > adj[maxn];

int main() {
  memset(dist, 0x3f, sizeof (dist));
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    u--, v--;
    adj[u].emplace_back(v, c);
    adj[v].emplace_back(u, c);
  }
  priority_queue<tuple<int, int, int> > q;
  dist[0][0] = 0;
  q.emplace(0,0,0);
  while (!q.empty()) {
    auto [d, v, p] = q.top();
    d = -d;
    q.pop();
    if (dist[v][p] != d) continue;
    if (v == n - 1 && p == 0) {
      printf("%d\n", d);
      return 0;
    }
    for (auto [u, c] : adj[v]) {
      if (dist[u][p ^ 1] > d + c) {
        dist[u][p ^ 1] = d + c;
        q.emplace(- d - c, u, p ^ 1);
      }
    }
  }
  puts("-1");
}

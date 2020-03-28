#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

constexpr int MAXN = 1e5 + 10;
int n, m;
ll dist[MAXN];
vi adj[MAXN], dd[MAXN], cc[MAXN], in_edges[MAXN];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v, d, c;
    scanf("%d%d%d%d", &u, &v, &d, &c);
    u--, v--;
    adj[u].push_back(v);
    dd[u].push_back(d);
    cc[u].push_back(c);
    adj[v].push_back(u);
    dd[v].push_back(d);
    cc[v].push_back(c);
  }
  memset(dist, 0x3f, sizeof(dist));
  dist[0] = 0;
  priority_queue<pair<ll, int>> q;
  q.emplace(0, 0);
  while (!q.empty()) {
    ll d_u = -q.top().first;
    int u = q.top().second;
    q.pop();
    if (d_u != dist[u]) continue;
    for (size_t i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i];
      int d = dd[u][i];
      if (dist[v] == -1 || dist[v] > dist[u] + d) {
        dist[v] = dist[u] + d;
        in_edges[v].clear();
        q.emplace(-dist[v], v);
      }
      if (dist[v] == dist[u] + d) in_edges[v].push_back(cc[u][i]);
    }
  }
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    ans += *min_element(in_edges[i].begin(), in_edges[i].end());
  }
  printf("%lld\n", ans);
}

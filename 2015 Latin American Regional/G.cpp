#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e4 + 10;
constexpr double eps = 1e-9;

int cmp(double a, double b) {
  return a <= b + eps ? a + eps < b ? -1 : 0 : 1;
}

int n, m;
double a[maxn], b[maxn], ans, dis[maxn];
priority_queue<pair<double, int> > q;
vector<pair<int, int> > adj[maxn];

double dijkstra(double x) {
  for (int i = 1; i < n; i++) dis[i] = 1e18;
  while (!q.empty()) q.pop();
  q.emplace(0.0, 0);
  while (!q.empty()) {
    auto [d, v] = q.top();
    d = -d;
    q.pop();
    if (cmp(d, dis[v]) != 0) continue;
    if (v == n - 1) {
      ans = max(ans, d);
      return d;
    }
    for (auto [u, i] : adj[v]) {
      double du = d + x * a[i] + b[i];
      if (cmp(dis[u], du) > 0) {
        dis[u] = du;
        q.emplace(-du, u);
      }
    }
  }
  assert(0);
  return -1.0;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    scanf("%lf%lf", &a[i], &b[i]);
  }
  double l = 0, r = 24 * 60;
  dijkstra(l);
  dijkstra(r);
  for (int i = 0; i < 50; i++) {
    double ta = l + (r - l) / 3.0;
    double tb = l + 2.0 * (r - l) / 3.0;
    if (dijkstra(ta) > dijkstra(tb)) r = tb;
    else l = ta;
  }
  printf("%.5f\n", ans);
}

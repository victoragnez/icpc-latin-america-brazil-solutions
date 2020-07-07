#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 0x3f3f3f3f;
constexpr int N = 222, M = N * N;

namespace flow {
  int y[M], nxt[M], gap[N], fst[N], c[N], pre[N], q[N], dis[N], f[M];
  int S, T, tot, Tn;
  void init(int s, int t, int tn) {
    tot = 1;
    for (int i = 0; i < tn; i++) fst[i] = 0;
    S = s;
    T = t;
    Tn = tn;
  }
  void add(int u, int v, int c1, int c2 = 0) {
    tot++; y[tot] = v; f[tot] = c1; nxt[tot] = fst[u]; fst[u] = tot;
    tot++; y[tot] = u; f[tot] = c2; nxt[tot] = fst[v]; fst[v] = tot;
  }
  int maxflow() {
    int u = S, t = 1, flow = 0;
    for (int i = 0; i < Tn; i++) {
      c[i] = fst[i];
      dis[i] = Tn;
      gap[i] = 0;
    }
    q[0] = T;
    dis[T] = 0;
    pre[S] = 0;
    for (int i = 0; i < t; i++) {
      int v = q[i];
      for (int j = fst[v]; j; j = nxt[j]) {
        if (dis[y[j]] > dis[v] + 1 && f[j ^ 1]) {
          q[t++] = y[j];
          dis[y[j]] = dis[v] + 1;
        }
      }
    }
    for (int i = 0; i < Tn; i++) gap[dis[i]]++;
    while (dis[S] <= Tn) {
      while (c[u] && (!f[c[u]] || dis[y[c[u]]] + 1 != dis[u])) c[u] = nxt[c[u]];
      if (c[u]) {
        pre[y[c[u]]] = c[u] ^ 1;
        u = y[c[u]];
        if (u == T) {
          int minf = inf;
          for (int p = pre[T]; p; p = pre[y[p]]) minf = min(minf,f[p ^ 1]);
          for (int p = pre[T]; p; p = pre[y[p]]) f[p ^ 1] -= minf, f[p] += minf;
          flow += minf;u = S;
        }
      } else {
        if (!(--gap[dis[u]])) break;
        int mind = Tn;
        c[u] = fst[u];
        for (int j = fst[u]; j; j = nxt[j]) {
          if (f[j] && dis[y[j]] < mind) {
            mind = dis[y[j]];
            c[u] = j;
          }
        }
        dis[u] = mind + 1;
        gap[dis[u]]++;
        if (u != S) u = y[pre[u]];
      }
    }
    return flow;
  }
}

vector<int> vet[N], query;
int n, q;

int solve(bool strict) {
  int s = 2 * n + 2, t = 2 * n + 3;
  flow::init(s, t, t + 1);
  for (int i = 0; i < n; i++) {
    flow::add(s, i + 1, 1);
    for (int v : vet[i]) flow::add(i + 1, v + n + 1, 1);
    if (!strict && (int) vet[i].size() != n) flow::add(i + 1, n + 1, 1);
  }
  for (int v : query) flow::add(v + n + 1, t, strict ? 1 : n);
  flow::add(n + 1, t, n);
  return flow::maxflow();
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    vet[i].resize(k);
    for (int j = 0; j < k; j++) scanf("%d", &vet[i][j]);
  }
  while (q--) {
    int k;
    scanf("%d", &k);
    query.resize(k);
    for (int i = 0; i < k; i++) scanf("%d", &query[i]);
    if (solve(true) == k && solve(false) == n) puts("Y");
    else puts("N");
  }
}

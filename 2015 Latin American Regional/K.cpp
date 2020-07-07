#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1e5 + 10;
constexpr int inf = 0x3f3f3f3f;
int n, m, vet[maxn], suf[maxn], dp[maxn], bit[maxn];
vector<pair<int, int> > shops[maxn];

void upd(int p, int v) {
  for(p++; p < maxn; p += p & -p) bit[p] = min(v, bit[p]);
}

int query(int p) {
  int ret = inf;
  for(p++; p > 0; p -= p & -p) ret = min(bit[p], ret);
  return ret;
}

int main() {
  memset(bit, 0x3f, sizeof (bit));
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &vet[i]);
  for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] + vet[i];
  while (m--) {
    int u, w, c;
    scanf("%d%d%d", &u, &w, &c);
    shops[u - 1].emplace_back(w, c);
  }
  for (int i = n - 1; i >= 0; i--) {
    dp[i] = inf;
    for (auto [w, c] : shops[i]) {
      if (w < vet[i]) continue;
      if (w >= suf[i]) {
        dp[i] = min(dp[i], c);
        continue;
      }
      int l = i + 1, r = n - 2, md;
      while (l <= r) {
        md = (l + r) >> 1;
        if (suf[i] - suf[md + 1] <= w) l = md + 1;
        else r = md - 1;
      }
      dp[i] = min(dp[i], c + query(l));
    }
    upd(i, dp[i]);
  }
  printf("%d\n", (dp[0] == inf) ? -1 : dp[0]);
}

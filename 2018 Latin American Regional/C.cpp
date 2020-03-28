#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e4 + 10;
int n, dp[MAXN], d[MAXN], c[MAXN];

int solve(int i) {
  if (i >= n) return 0;
  int& ret = dp[i];
  if (ret != -1) return ret;
  int cost = 4 * c[i], t = d[i];
  ret = cost + solve(i + 1);
  for (int j = 1; j < 6; j++) {
    if (t >= 120) break;
    cost += c[i + j];
    if (j == 1) cost += c[i + j];
    t += d[i + j];
    ret = min(ret, cost + solve(i + j + 1));
  }
  return ret;
}

int main() {
  memset(dp, -1, sizeof(dp));
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d%d", d + i, c + i);
  printf("%.2f\n", solve(0) * 0.25);
}

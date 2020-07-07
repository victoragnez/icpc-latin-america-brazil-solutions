#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m, ans = 0, pos[] = {10000, 1000, 100, 10, 1};
  scanf("%d%d", &m, &n);
  for (int i = 0; i < n; i++) {
    int b, s = 0, v0 = 0;
    scanf("%d", &b);
    for (int j = 0; j < m; j++) {
      int t;
      scanf("%d", &t);
      if (j == 0) v0 = t;
      else s += t;
    }
    int best = max(0, b - s), actual = (s + v0 <= b ? v0 : 0);
    for (int v : pos) {
      if (v <= best) {
        best = v;
        break;
      }
    }
    ans += best - actual;
  }
  printf("%d\n", ans);
}

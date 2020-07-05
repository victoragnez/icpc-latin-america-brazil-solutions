#include <stdio.h>

int main() {
  int n, c, ans = 0, b = -0x3f3f3f3f;
  scanf("%d%d", &n, &c);
  for (int i = 0; i < n; i++) {
    int v, pr = ans;
    scanf("%d", &v);
    if (b + v > ans) ans = b + v;
    if (pr - v - c > b) b = pr - v - c;
  }
  printf("%d\n", ans);
}

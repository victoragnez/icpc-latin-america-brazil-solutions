#include <stdio.h>

int main() {
  int v, t, ans = 0;
  scanf("%d", &v);
  for (int i = 0; i < 5; i++) {
    scanf("%d", &t);
    if (t == v) ans++;
  }
  printf("%d\n", ans);
}

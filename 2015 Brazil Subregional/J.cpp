#include <stdio.h>

int n, m, vet[505], ans;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int v;
      scanf("%d", &v);
      vet[j] += v;
      if (vet[j] >= vet[ans]) ans = j;
    }
  }
  printf("%d\n", ans + 1);
}

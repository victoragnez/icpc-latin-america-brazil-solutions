#include<stdio.h>

int main() {
  int fat[10];
  fat[0] = 1;
  for (int i = 1; i < 10; i++) fat[i] = fat[i - 1] * i;
  int n, ans = 0;
  scanf("%d", &n);
  for (int i = 9; i > 0; i--) {
    ans += n / fat[i];
    n %= fat[i];
  }
  printf("%d\n", ans);
}

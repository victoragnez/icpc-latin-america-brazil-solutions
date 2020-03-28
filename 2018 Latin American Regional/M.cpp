#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, ans = 0, last = -1;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int v;
    scanf("%d", &v);
    if (v > last) ans++;
    last = v;
  }
  printf("%d\n", ans);
}

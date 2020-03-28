#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int MAXN = 1e5 + 10;
ll v[MAXN], tot;

int main() {
  int n, cnt = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", v + i);
    tot += v[i];
    if (i > 0) v[i] += v[i - 1];
  }
  int j = 0;
  ll cur = 0;
  for (int i = 0; i < n; i++) {
      while (j < n - 1 && 2 * (v[j] - cur) < tot) j++;
      if (j < n - 1 && 2 * (v[j] - cur) == tot) cnt++;
      cur = v[i];
  }
  puts(cnt > 1 ? "Y" : "N");
}

#include <stdio.h>
using ll = long long;

int main() {
  ll n, m;
  scanf("%lld%lld", &n, &m);
  ll l = 1, r = n / 2, md;
  while (l <= r) {
    md = (l + r) / 2;
    if (n * n - (n - 2 * md) * (n - 2 * md) < m) l = md + 1;
    else r = md - 1;
  }
  ll x = l, y = l;
  l--;
  m -= (n * n) - (n - 2 * l) * (n - 2 * l) + 1;
  ll d = 0, q = n - 2 * l;
  while (m > 0) {
    static int mx[] = {0, 1, 0, -1}, my[] = {1, 0, -1, 0};
    ll v = q - 1;
    if (m < v) v = m;
    m -= v;
    x += v * mx[d];
    y += v * my[d];
    d++;
    if (d == 4) d = 0, q--;
  }
  printf("%lld %lld\n", x, y);
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct point {
  ll x, y;
};

point operator-(const point& a, const point& b) {
  return {a.x - b.x, a.y - b.y};
}

ll cross(const point& a, const point& b) {
  return a.x * b.y - b.x * a.y;
}

constexpr int maxn = 1e5 + 10;
point vet[maxn];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld%lld", &vet[i].x, &vet[i].y);
  ll tot = 0;
  for (int i = 0; i < n; i++) tot += cross(vet[i], vet[(i + 1) % n]);
  ll ans = 0, cur = 0;
  int j = 1;
  for (int i = 0; i < n; i++) {
    auto v = cross(vet[j] - vet[i], vet[(j + 1) % n] - vet[i]);
    while ((j + 2) % n != i && (2 * (cur + v) <= tot  || j == (i + 1) % n)) {
      cur += v;
      j = (j + 1) % n;
      v = cross(vet[j] - vet[i], vet[(j + 1) % n] - vet[i]);
    }
    if (2 * cur <= tot) {
      ll u = cur;
      if ((j + 2) % n != i) u = max(u, tot - cur - v);
      ans = max(ans, tot - u);
    } else {
      ans = max(ans, tot - cur);
    }
    cur -= cross(vet[i] - vet[j], vet[(i + 1) % n] - vet[j]);
  }
  printf("%lld %lld\n", ans, tot - ans);
}

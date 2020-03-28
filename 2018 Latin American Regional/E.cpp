#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int cmp(ll x, ll y = 0) { return (x <= y) ? (x < y) ? -1 : 0 : 1; }
struct point {
  ll x, y;
  point() : x(0), y(0) {}
  point(ll X, ll Y) : x(X), y(Y) {}
  point operator-(point a) { return point(x - a.x, y - a.y); }
  ll operator%(point a) { return x * a.y - y * a.x; }
};
int ccw(point a, point b, point c) { return cmp((b - a) % (c - a)); }

constexpr int MAXN = 1e5 + 10;
int n;
point vet[MAXN];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld%lld", &vet[i].x, &vet[i].y);
  const auto edge = [](int p) { return vet[(p + 1) % n] - vet[p % n]; };
  ll ans = (ll) n * (n - 1) * (n - 2) / 6;
  for (int i = 0, j = 1; i < n; i++) {
    point pi = edge(i), pj = edge(j);
    while (ccw({}, pi, pj) >= 0) pj = edge(++j);
    ans -= (ll) (j - i - 1) * (j - i - 2) / 2;
  }
  printf("%lld\n", ans);
}

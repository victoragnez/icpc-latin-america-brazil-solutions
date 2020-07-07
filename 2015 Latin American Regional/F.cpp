#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

constexpr int maxn = 2e5 + 10;
bool bit[maxn];

void upd(int p) {
  for(p++; p < maxn; p += p & -p) bit[p] ^= 1;
}

bool query(int p) {
  bool ret = 0;
  for(p++; p > 0; p -= p & -p) ret ^= bit[p];
  return ret;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<tuple<int, bool, int, int> > events;
  vector<int> aux;
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    aux.push_back(y);
    events.emplace_back(x, true, y, i);
  }
  int fstx = -1, fsty = -1, lstx = -1, lsty = -1;
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    aux.push_back(y);
    if (i == 0) {
      fstx = x;
      fsty = y;
    }
    if (i > 0 && x == lstx) events.emplace_back(x, false, lsty, y);
    lstx = x;
    lsty = y;
  }
  if (fstx == lstx) events.emplace_back(fstx, false, fsty, lsty);
  sort(aux.begin(), aux.end());
  sort(events.begin(), events.end());
  long long ans = 0;
  for (auto [x, pt, y1, y2] : events) {
    y1 = (int) (lower_bound(aux.begin(), aux.end(), y1) - aux.begin());
    if (pt) {
      if (!query(y1)) ans += y2 + 1;
    } else {
      y2 = (int) (lower_bound(aux.begin(), aux.end(), y2) - aux.begin());
      upd(y1);
      upd(y2);
    }
  }
  printf("%lld\n", ans);
}


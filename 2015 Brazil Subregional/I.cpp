#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

vector<vector<pii> > omns[11];
vector<vector<unsigned> > masks[11];
vector<pii> dims[11];

int main() {
  omns[1].push_back({{0,0}});
  for (int i = 1; i < 11; i++) {
    if (i > 1) {
      for (auto& vet : omns[i - 1]) {
        constexpr int mx[] = {1, -1, 0, 0}, my[] = {0, 0, 1, -1};
        for (int k = 0; k < 4; k++) {
          for (int j = 0; j < (int) vet.size(); j++) {
            auto cur = vet;
            cur.emplace_back(vet[j].first + mx[k], vet[j].second + my[k]);
            sort(cur.begin(), cur.end());
            auto fst = cur[0];
            for (auto& v : cur) fst.second = min(fst.second, v.second);
            for (auto& v : cur) v.first -= fst.first, v.second -= fst.second;
            cur.resize(unique(cur.begin(), cur.end()) - cur.begin());
            if (i == (int) cur.size()) omns[i].push_back(move(cur));
          }
        }
      }
      sort(omns[i].begin(), omns[i].end());
      omns[i].resize(unique(omns[i].begin(), omns[i].end()) - omns[i].begin());
    }
    for (auto& v : omns[i]) {
      int x = 0, y = 0;
      for (auto& p : v) {
        x = max(x, p.first + 1);
        y = max(y, p.second + 1);
      }
      dims[i].emplace_back(x, y);
      masks[i].emplace_back(x);
      for (auto& p : v) masks[i].back()[p.first] |= (1 << p.second);
    }
  }
  int t;
  scanf("%d", &t);
  while (t--) {
    int r, c, h, n;
    scanf("%d%d%d%d", &r, &c, &h, &n);
    static unsigned grid[31][31];
    memset(grid, 0xff, sizeof(grid));
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        int v;
        scanf("%d", &v);
        for (int x = v; x <= h; x++) grid[x][i] ^= (1 << j);
      }
    }
    int ans = 0;
    for (int id = 0; id < (int) masks[n].size(); id++) {
      const int dx = dims[n][id].first, dy = dims[n][id].second;
      const auto& vet = masks[n][id];
      int best = h;
      for (int i = 0; i < r - dx + 1; i++) {
        for (int j = 0; j < c - dy + 1; j++) {
          while (best > 0) {
            bool ok = true;
            for (int l = 0; l < dx; l++) {
              if (vet[l] & (grid[best - 1][i + l] >> j)) {
                ok = false;
                break;
              }
            }
            if (!ok) break;
            best--;
          }
        }
      }
      ans += h - best;
    }
    printf("%d\n", ans);
  }
}

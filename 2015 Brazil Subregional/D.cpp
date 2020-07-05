#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  map<string, int> ans;
  set<string> unknown;
  vector<pair<vector<string>, int> > eq;
  vector<vector<string> > grid(n, vector<string>(m));
  vector<int> lines(n), cols(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char v[3];
      scanf("%s", v);
      grid[i][j] = v;
      unknown.insert(grid[i][j]);
    }
    scanf("%d", &lines[i]);
  }
  for (int j = 0; j < m; j++) scanf("%d", &cols[j]);
  for (int i = 0; i < n; i++) eq.emplace_back(grid[i], lines[i]);
  for (int j = 0; j < m; j++) {
    vector<string> col;
    for (int i = 0; i < n; i++) col.push_back(grid[i][j]);
    eq.emplace_back(col, cols[j]);
  }
  while (!unknown.empty()) {
    for (auto& [vars, res] : eq) {
      int count_unknown = 0, freq = 0;
      string x;
      for (auto& s : vars) {
        if (s != x && unknown.find(s) != unknown.end()) {
          x = s;
          count_unknown++;
          if (count_unknown > 1) break;
        }
        if (x == s) freq++;
      }
      if (count_unknown == 1) {
        unknown.erase(x);
        int vx = res / freq;
        for (auto& [tvars, tres] : eq) {
          for (auto& s : tvars) {
            if (s == x) tres -= vx;
          }
        }
        ans[x] = vx;
      }
    }
  }
  for (auto [k, v] : ans) {
    printf("%s %d\n", k.c_str(), v);
  }
}

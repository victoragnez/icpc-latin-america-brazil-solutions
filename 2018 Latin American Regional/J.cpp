#include <bits/stdc++.h>
using namespace std;

constexpr auto MAXN = 101;
int n, m, w, grid[MAXN][MAXN], pos[MAXN][MAXN], ord[MAXN];
bool removed[MAXN];
map<string, int> trad;
vector<string> names;

bool check() {
  static bool processed[MAXN];
  static int best_pos[MAXN], against[MAXN];
  for (int i = 0; i < n; i++) best_pos[i] = m - 1;
  memset(processed, 0, sizeof(processed));
  memset(against, 0, sizeof(against));
  processed[w] = 1;
  queue<int> q;
  q.push(w);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < n; i++) {
      while (best_pos[i] > pos[v][i]) {
        against[grid[i][best_pos[i]--]]++;
      }
    }
    for (int i = 0; i < m; i++) {
      if (removed[i] || processed[i]) continue;
      if (against[i] + against[i] > n) {
        processed[i] = true;
        q.push(i);
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (!removed[i] && !processed[i]) return false;
  }
  return true;
}

int get(string s) {
  if (trad.find(s) == trad.end()) {
    trad[s] = (int) names.size();
    names.push_back(s);
  }
  return trad[s];
}

int main() {
  static int pref[MAXN], votes[MAXN];
  scanf("%d%d", &m, &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char s[11];
      scanf("%s", s);
      int v = get(s);
      grid[i][j] = v;
      pos[v][i] = j;
    }
  }
  {
    char s[11];
    scanf("%s", s);
    w = get(s);
    int it = 0;
    for (auto&& p : trad) ord[it++] = p.second;
    for (int i = 0; i < n; i++) votes[grid[i][0]]++;
  }
  vector<int> ans;
  for (int it = 0; it < m; it++) {
    int id = -1;
    for (int i = 0; i < m; i++) {
      int v = ord[i];
      if (removed[v]) continue;
      removed[v] = true;
      if (v == w && votes[v] + votes[v] > n) {
        id = v;
        break;
      } else if (votes[v] + votes[v] < n && v != w && check()) {
        id = v;
        break;
      } else removed[v] = false;
    }
    if (id == -1) {
      puts("*");
      return 0;
    }
    ans.push_back(id);
    if (id == w) {
      for (int i = 0; i < m; i++) {
        int v = ord[i];
        if (!removed[v]) ans.push_back(v);
      }
      break;
    }
    for (int i = 0; i < n; i++) {
      while (removed[grid[i][pref[i]]]) {
        votes[grid[i][pref[i]]]--;
        pref[i]++;
        votes[grid[i][pref[i]]]++;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    printf("%s%c", names[ans[i]].c_str(), ((i == m - 1) ? '\n' : ' '));
  }
}

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

constexpr int MAXN = (1 << 18) + 10;
int vet[MAXN], aux[MAXN];
bool rm[MAXN];
vi cur;
vector<vi> sol;

void solve(int l, int r) {
  int sz = r - l;
  if (sz == 1) {
    if (vet[l] == 0) sol.push_back(cur);
    return;
  }
  for (int i = 0; i < sz; i++) rm[i] = false;
  int diff = vet[r - 1] - vet[r - 2], j = 1, it = 0;
  for (int i = 0; i < sz; i++) {
    if (rm[i]) continue;
    j = max(j, i + 1);
    int val = vet[l + i];
    while (j < sz && vet[l + j] < val + diff) j++;
    if (j >= sz || vet[l + j] > val + diff) return;
    rm[j] = true;
    vet[l + it] = val;
    aux[it++] = val + diff;
    j++;
  }
  for (int i = 0; i < it; i++) vet[l + it + i] = aux[i];

  cur.push_back(diff);
  solve(l, l + it);
  cur.pop_back();

  cur.push_back(-diff);
  solve(l + it, r);
  cur.pop_back();
}

int main() {
  int n;
  scanf("%d", &n);
  cur.reserve(n);
  n = (1 << n);
  for (int i = 0; i < n; i++) scanf("%d", &vet[i]);
  sort(vet, vet + n);
  solve(0, n);
  for (auto&& v : sol) sort(v.begin(), v.end());
  sort(sol.begin(), sol.end());
  sol.resize(unique(sol.begin(), sol.end()) - sol.begin());
  for (auto&& v : sol) {
    int sz = (int) v.size();
    for (int i = 0; i < sz; i++) {
      printf("%d%c", v[i], ((i == sz - 1) ? '\n' : ' '));
    }
  }
}

#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

constexpr int MAXN = 1e5 + 10;
int ans[MAXN], biggest[MAXN], bit[MAXN];
tuple<int, int, int> qs[MAXN];

void upd(int p, int v) {
  for (; p < MAXN; p += p & -p) bit[p] += v;
}

int query(int p) {
  int ret = 0;
  for (; p > 0; p -= p & -p) ret += bit[p];
  return ret;
}

int main() {
  for (int i = 2; i < MAXN; i++) {
    if (!biggest[i]) {
      for (int j = i; j < MAXN; j += i) {
        biggest[j] = i;
      }
    }
  }
  vi multiples[MAXN];
  for (int i = 0; i < MAXN; i++) {
    multiples[biggest[i]].push_back(i);
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int n, k;
    scanf("%d%d", &n, &k);
    qs[i] = {k, n, i};
  }
  sort(qs, qs + q);
  int nxt_k = 2;
  for (int i = 0; i < q; i++) {
    int k, n, id;
    tie(k, n, id) = qs[i];
    while (nxt_k <= k) {
      for (int v : multiples[nxt_k]) upd(v, 1);
      nxt_k++;
    }
    ans[id] = query(n);
  }
  for (int i = 0; i < q; i++) {
    printf("%d\n", ans[i]);
  }
}

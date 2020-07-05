#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  vector<long long> vet;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    long long v = 0;
    for (int j = 0; j < k; j++) {
      int t;
      scanf("%d", &t);
      if (t & 1) v |= (1LL << j);
    }
    for (auto u : vet) v = min(v, u ^ v);
    if (v > 0) vet.push_back(v);
  }
  if (k > (int) vet.size() || n == k) puts("S");
  else puts("N");
}

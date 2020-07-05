#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 3e3 + 10;
constexpr int inf = 0x3f3f3f3f;

int n, ans;
pair<int, int> vet[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &vet[i].first, &vet[i].second);
  }
  sort(vet, vet + n);
  for (int i = 0; i < n; i++) {
    int l = -inf, r = inf;
    for (int j = i + 1; j < n; j++) {
      if (vet[j].second > vet[i].second && vet[j].second < r) {
        r = vet[j].second;
        ans++;
      }
      if (vet[j].second < vet[i].second && vet[j].second > l) {
        l = vet[j].second;
        ans++;
      }
    }
  }
  printf("%d\n", ans);
}

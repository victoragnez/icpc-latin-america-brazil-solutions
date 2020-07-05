#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e3 + 10;
int n, vet[maxn];
char s[maxn];
pair<int, int> dp[maxn][maxn];

int main() {
  scanf("%s", s);
  n = (int) strlen(s);
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; i++) {
    int p;
    scanf("%d", &p);
    vet[p - 1] = 1;
  }
  for (int i = 0; i < n; i++) dp[i][i] = {vet[i], 1};
  for (int t = 2; t <= n; t++) {
    for (int l = 0; l < n - t + 1; l++) {
      int r = l + t - 1;
      dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
      if (s[l] == s[r]) {
        auto aux = dp[l + 1][r - 1];
        aux.first += vet[l] + vet[r];
        aux.second += 2;
        dp[l][r] = max(dp[l][r], aux);
      }
    }
  }
  printf("%d\n", dp[0][n - 1].second);
}

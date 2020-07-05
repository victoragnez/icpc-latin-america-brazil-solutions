#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 110;
constexpr long long mod = 1e9 + 7;
long long dp[maxn][maxn], choose[maxn][maxn];

int main() {
  choose[0][0] = 1;
  for(int i = 1; i < maxn; i++){
      choose[i][0] = 1;
      for(int j = 1; j <= i; j++){
          choose[i][j] = choose[i-1][j] + choose[i-1][j-1];
          if (choose[i][j] >= mod) choose[i][j] -= mod;
      }
  }
  int n, k;
  scanf("%d%d", &n, &k);
  if (n == 1) {
    puts("1");
    return 0;
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n - 2; j++) {
      for (int q = 0; q <= min(k - 1, j); q++) {
        dp[i][j] += choose[j][q] * dp[i - 1][j - q];
        dp[i][j] %= mod;
      }
    }
  }
  printf("%d\n", (int) dp[n][n - 2]);
}

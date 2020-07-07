#include <stdio.h>
using ll = long long;

constexpr int maxn = 5e3 + 10;
constexpr ll mod = 1e9 + 7;
ll fat[maxn], ifat[maxn], va[maxn], vb[maxn];

ll modpow(ll b, ll e) {
  ll ret = 1;
  while(e > 0){
    if (e & 1) ret = ret * b % mod;
    b = b * b % mod;
    e >>= 1;
  }
  return ret;
}

ll invmod(ll val) {
  return modpow(val, mod - 2);
}

ll choose(int n, int k) {
  if (k < 0 || k > n) return 0;
  return ((fat[n] * ifat[k] % mod) * ifat[n - k] % mod);
}

int main() {
  fat[0] = ifat[0] = 1;
  for(int i = 1; i < maxn; i++) {
    fat[i] = (ll) i * fat[i-1] % mod;
    ifat[i] = invmod(fat[i]);
  }
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n + 1; i++) {
    va[i] = choose(n, i);
    vb[i] = modpow(i, n);
  }
  while (q--) {
    int k;
    scanf("%d", &k);
    if (k > n) k = n;
    ll ans = 0;
    for (int i = 0; i <= k; i++) {
      ll val = va[i] * vb[k - i] % mod;
      if (i & 1) ans += mod - val;
      else ans += val;
      if (ans >= mod) ans -= mod;
    }
    printf("%d%c", (int) ans, (q > 0) ? ' ' : '\n');
  }
}

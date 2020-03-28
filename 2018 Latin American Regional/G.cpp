#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MAXN = 1e3 + 10;
constexpr ll mod = 1e9 + 7;
int n, sz[MAXN];
pii vet[MAXN];
ll ans, fat[MAXN], ifat[MAXN];

struct frac {
  ll num, den;
  frac() = default;
  frac(ll a, ll b) : num(a), den(b) { }
  bool operator<(const frac& f) const { return num * f.den < f.num * den; }
  bool operator==(const frac& f) const { return num * f.den == f.num * den; }
};

int pnts_sz;
frac pnts[MAXN * MAXN];
map<int, vi> ints[MAXN * MAXN];
vector<vi> gps[MAXN * MAXN];

ll modpow(ll b, ll e) {
  ll ret = 1;
  while (e > 0) {
    if (e & 1) ret = (ret * b) % mod;
    b = (b * b) % mod;
    e >>= 1;
  }
  return ret;
}

int main() {
  fat[0] = ifat[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    fat[i] = (i * fat[i - 1]) % mod;
    ifat[i] = modpow(fat[i], mod - 2);
  }
  const auto no_inter = [](int i, int j) {
    return (vet[j].first <= vet[i].first && vet[j].second <= vet[i].second) ||
        (vet[i].first <= vet[j].first && vet[i].second <= vet[j].second);
  };
  scanf("%d", &n);
  int it = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &vet[it].first, &vet[it].second);
    sz[it] = 1;
    for (int j = 0; j < it; j++) {
      if (vet[j].first == vet[it].first && vet[j].second == vet[it].second) {
        sz[j] += sz[it];
        sz[it] = 0;
        it--;
        break;
      }
      if (no_inter(it, j)) continue;
      int da = vet[it].first - vet[j].first;
      int db = vet[j].second - vet[it].second;
      if (da < 0) {
        da = -da;
        db = -db;
      }
      int d = __gcd(da, db);
      da /= d;
      db /= d;
      pnts[pnts_sz++] = {db, da + db};
    }
    it++;
  }
  n = it;
  sort(pnts, pnts + pnts_sz);
  pnts_sz = (int) (unique(pnts, pnts + pnts_sz) - pnts);
  ll tot = 1;
  for (int i = 0; i < n; i++) {
    tot = (tot * fat[sz[i]]) % mod;
  }
  ans = tot;
  ll neg_tot = (mod - tot) % mod;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (no_inter(i, j)) continue;
      int da = vet[i].first - vet[j].first;
      int db = vet[j].second - vet[i].second;
      if (da < 0) {
        da = -da;
        db = -db;
      }
      int d = __gcd(da, db);
      da /= d;
      db /= d;
      frac f{db, da + db};
      int p = (int) (lower_bound(pnts, pnts + pnts_sz, f) - pnts);
      int fx = db * vet[i].first + da * vet[i].second;
      vi& s = ints[p][fx];
      s.push_back(i);
      s.push_back(j);
    }
  }
  for (int i = 0; i < pnts_sz; i++) {
    for (auto&& p : ints[i]) {
      vi& v = p.second;
      sort(v.begin(), v.end());
      v.resize(unique(v.begin(), v.end()) - v.begin());
      gps[i].push_back(move(v));
    }
  }
  for (int i = 0; i < pnts_sz; i++) {
    ll cur = tot;
    for (auto&& gp : gps[i]) {
      int cnt = 0;
      for (int v : gp) {
        cnt += sz[v];
        cur = (cur * ifat[sz[v]]) % mod;
      }
      cur = (cur * fat[cnt]) % mod;
    }
    ans += cur;
    if (ans >= mod) ans -= mod;
    ans += neg_tot;
    if (ans >= mod) ans -= mod;
  }
  printf("%lld\n", ans);
}

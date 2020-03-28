#include <bits/stdc++.h>
using namespace std;

// bigint is required only if __int128_t is not available
struct bigint {
  static constexpr int base = 1000000000;
  static constexpr int base_digits = 9;
  vector<int> a;
  int sign;
  bigint() : sign(1) {}
  bigint(long long v) { *this = v; }
  explicit bigint(const string &s) { read(s); }

  bigint(const bigint &v) = default;
  bigint& operator=(const bigint &v) = default;
  bigint(bigint &&v) = default;
  bigint& operator=(bigint &&v) = default;

  void operator=(long long v) {
    sign = 1;
    a.clear();
    if (v < 0) sign = -1, v = -v;
    for (; v > 0; v = v / base) a.push_back((int) (v % base));
  }

  bigint operator+(const bigint &v) const {
    if (sign == v.sign) {
      bigint res = v;
      for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
        if (i == (int) res.a.size()) res.a.push_back(0);
        res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
        carry = res.a[i] >= base;
        if (carry) res.a[i] -= base;
      }
      return res;
    }
    return *this - (-v);
  }

  bigint operator-(const bigint &v) const {
    if (sign == v.sign) {
      if (abs() >= v.abs()) {
        bigint res = *this;
        for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
          res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
          carry = res.a[i] < 0;
          if (carry) res.a[i] += base;
        }
        res.trim();
        return res;
      }
      return -(v - *this);
    }
    return *this + (-v);
  }

  void operator*=(int v) {
    if (v < 0) sign = -sign, v = -v;
    for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
      if (i == (int) a.size()) a.push_back(0);
      long long cur = a[i] * (long long) v + carry;
      carry = (int) (cur / base);
      a[i] = (int) (cur % base);
    }
    trim();
  }

  bigint operator*(int v) const {
    bigint res = *this;
    res *= v;
    return res;
  }

  void operator*=(long long v) {
    if (v < 0) sign = -sign, v = -v;
    if (v > base) {
      *this = *this * (v / base) * base + *this * (v % base);
      return;
    }
    for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
      if (i == (int) a.size()) {
        a.push_back(0);
      }
      long long cur = a[i] * (long long) v + carry;
      carry = (int) (cur / base);
      a[i] = (int) (cur % base);
    }
    trim();
  }

  bigint operator*(long long v) const {
    bigint res = *this;
    res *= v;
    return res;
  }

  friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1);

  bigint operator/(const bigint &v) const {
    return divmod(*this, v).first;
  }

  bigint operator%(const bigint &v) const {
    return divmod(*this, v).second;
  }

  void operator/=(int v) {
    if (v < 0) sign = -sign, v = -v;
    for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
      long long cur = a[i] + rem * (long long) base;
      a[i] = (int) (cur / v);
      rem = (int) (cur % v);
    }
    trim();
  }

  bigint operator/(int v) const {
    bigint res = *this;
    res /= v;
    return res;
  }

  int operator%(int v) const {
    if (v < 0) v = -v;
    int m = 0;
    for (int i = (int) a.size() - 1; i >= 0; --i) {
      m = (int) ((a[i] + m * (long long) base) % v);
    }
    return m * sign;
  }

  void operator+=(const bigint &v) {
    *this = *this + v;
  }
  void operator-=(const bigint &v) {
    *this = *this - v;
  }
  void operator*=(const bigint &v) {
    *this = *this * v;
  }
  void operator/=(const bigint &v) {
    *this = *this / v;
  }
  void operator%=(const bigint &v) {
    *this = *this % v;
  }

  bool operator<(const bigint &v) const {
    if (sign != v.sign) return sign < v.sign;
    if (a.size() != v.a.size()) {
      return a.size() * sign < v.a.size() * v.sign;
    }
    for (int i = (int) a.size() - 1; i >= 0; i--) {
      if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
    }
    return false;
  }

  bool operator>(const bigint &v) const {
    return v < *this;
  }
  bool operator<=(const bigint &v) const {
    return !(v < *this);
  }
  bool operator>=(const bigint &v) const {
    return !(*this < v);
  }
  bool operator==(const bigint &v) const {
    return !(*this < v) && !(v < *this);
  }
  bool operator!=(const bigint &v) const {
    return *this < v || v < *this;
  }

  void trim() {
    while (!a.empty() && !a.back()) a.pop_back();
    if (a.empty()) sign = 1;
  }

  bigint operator-() const {
    bigint res = *this;
    res.sign = -sign;
    return res;
  }

  bigint abs() const {
    bigint res = *this;
    res.sign *= res.sign;
    return res;
  }

  long long longValue() const {
    long long res = 0;
    for (int i = (int) a.size() - 1; i >= 0; i--) {
      res = res * base + a[i];
    }
    return res * sign;
  }

  void read(const string &s) {
    sign = 1;
    a.clear();
    int pos = 0;
    while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
      if (s[pos] == '-') sign = -sign;
      ++pos;
    }
    for (int i = (int) s.size() - 1; i >= pos; i -= base_digits) {
      int x = 0;
      for (int j = max(pos, i - base_digits + 1); j <= i; j++) {
        x = x * 10 + s[j] - '0';
      }
      a.push_back(x);
    }
    trim();
  }

  friend ostream& operator<<(ostream &stream, const bigint &v);

  static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
    vector<long long> p(max(old_digits, new_digits) + 1);
    p[0] = 1;
    for (int i = 1; i < (int) p.size(); i++) p[i] = p[i - 1] * 10;
    vector<int> res;
    long long cur = 0;
    int cur_digits = 0;
    for (int i = 0; i < (int) a.size(); i++) {
      cur += a[i] * p[cur_digits];
      cur_digits += old_digits;
      while (cur_digits >= new_digits) {
        res.push_back((int) (cur % p[new_digits]));
        cur /= p[new_digits];
        cur_digits -= new_digits;
      }
    }
    res.push_back((int) cur);
    while (!res.empty() && !res.back()) res.pop_back();
    return res;
  }

  typedef vector<long long> vll;

  static vll karatsubaMultiply(const vll &a, const vll &b) {
    int n = (int) a.size();
    vll res(n + n);
    if (n <= 32) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          res[i + j] += a[i] * b[j];
        }
      }
      return res;
    }

    int k = n >> 1;
    vll a1(a.begin(), a.begin() + k);
    vll a2(a.begin() + k, a.end());
    vll b1(b.begin(), b.begin() + k);
    vll b2(b.begin() + k, b.end());

    vll a1b1 = karatsubaMultiply(a1, b1);
    vll a2b2 = karatsubaMultiply(a2, b2);

    for (int i = 0; i < k; i++) a2[i] += a1[i];
    for (int i = 0; i < k; i++) b2[i] += b1[i];

    vll r = karatsubaMultiply(a2, b2);
    for (int i = 0; i < (int) a1b1.size(); i++) r[i] -= a1b1[i];
    for (int i = 0; i < (int) a2b2.size(); i++) r[i] -= a2b2[i];

    for (int i = 0; i < (int) r.size(); i++) res[i + k] += r[i];
    for (int i = 0; i < (int) a1b1.size(); i++) res[i] += a1b1[i];
    for (int i = 0; i < (int) a2b2.size(); i++) res[i + n] += a2b2[i];
    return res;
  }

  bigint operator*(const bigint &v) const {
    vector<int> a6 = convert_base(this->a, base_digits, 6);
    vector<int> b6 = convert_base(v.a, base_digits, 6);
    vll a_(a6.begin(), a6.end());
    vll b(b6.begin(), b6.end());
    while (a_.size() < b.size()) a_.push_back(0);
    while (b.size() < a_.size()) b.push_back(0);
    while (a_.size() & (a_.size() - 1)) a_.push_back(0), b.push_back(0);
    vll c = karatsubaMultiply(a_, b);
    bigint res;
    res.sign = sign * v.sign;
    for (int i = 0, carry = 0; i < (int) c.size(); i++) {
      long long cur = c[i] + carry;
      res.a.push_back((int) (cur % 1000000));
      carry = (int) (cur / 1000000);
    }
    res.a = convert_base(res.a, 6, base_digits);
    res.trim();
    return res;
  }
};

pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
  int norm = bigint::base / (b1.a.back() + 1);
  bigint a = a1.abs() * norm;
  bigint b = b1.abs() * norm;
  bigint q, r;
  q.a.resize(a.a.size());
  for (int i = (int) a.a.size() - 1; i >= 0; i--) {
    r *= bigint::base;
    r += a.a[i];
    int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
    int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
    int d = (int) (((long long) bigint::base * s1 + s2) / b.a.back());
    r -= b * d;
    while (r < 0) r += b, --d;
    q.a[i] = d;
  }
  q.sign = a1.sign * b1.sign;
  r.sign = a1.sign;
  q.trim();
  r.trim();
  return make_pair(q, r / norm);
}

ostream& operator<<(ostream &stream, const bigint &v) {
  if (v.sign == -1) stream << '-';
  stream << (v.a.empty() ? 0 : v.a.back());
  for (int i = (int) v.a.size() - 2; i >= 0; --i) {
    stream << setw(bigint::base_digits) << setfill('0') << v.a[i];
  }
  return stream;
}

constexpr int MAXN = 101;
int n, m, p[11], grid[11][MAXN], pos[11][MAXN], len[11];
bigint ans;
vector<int> r, primes, pot;
bool nprime[MAXN];

void dfs(int i, int v) {
  len[i]++;
  int nxt = grid[i][v];
  if (pos[i][nxt] == -1) {
    pos[i][nxt] = pos[i][v] + 1;
    dfs(i, nxt);
  }
}

int modpow(int b, int e, int mod = INT_MAX) {
  int ret = 1;
  while (e > 0) {
    if (e & 1) ret = (ret * b) % mod;
    b = (b * b) % mod;
    e >>= 1;
  }
  return ret;
}

int modinv(int v, int b, int e, int mod) {
  int phi = (b - 1) * modpow(b, e - 1);
  return modpow(v, phi - 1, mod);
}

int main() {
  for (int i = 2; i < MAXN; i++) {
    if (!nprime[i]) {
      primes.push_back(i);
      for (int j = i * i; j < MAXN; j += i) nprime[j] = true;
    }
  }
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", p + i);
    p[i]--;
    for (int j = 0; j < m; j++) {
      scanf("%d", &grid[i][j]);
      grid[i][j]--;
    }
  }

  for (int t = 0; t < m; t++) {
    bool ok = true;
    for (int i = 1; i < n; i++) {
      if (p[i] != p[0]) {
        ok = false;
        break;
      }
    }
    if (ok) {
      printf("%d %d\n", p[0] + 1, t);
      return 0;
    }
    for (int i = 0; i < n; i++) p[i] = grid[i][p[i]];
  }

  memset(pos, -1, sizeof(pos));
  for (int i = 0; i < n; i++) {
    pos[i][p[i]] = 0;
    dfs(i, p[i]);
  }
  int id = -1;
  for (int goal = 0; goal < m; goal++) {
    bool ok = 1;
    bigint cur = 0, prod = 1;
    pot.assign(primes.size(), 0);
    r.assign(primes.size(), 0);
    r.clear();
    for (int i = 0; i < n; i++) {
      if (pos[i][goal] == -1) {
        ok = false;
        break;
      }
      for (int j = 0; j < i; j++) {
        auto d = __gcd(len[i], len[j]);
        if (pos[i][goal] % d != pos[j][goal] % d) {
          ok = false;
          break;
        }
      }
      if (!ok) break;
      for (size_t j = 0; j < primes.size(); j++) {
        int v = len[i], cnt = 0, val = 1;
        while (v % primes[j] == 0) {
          v /= primes[j];
          cnt++;
          val *= primes[j];
        }
        if (cnt > pot[j]) {
          pot[j] = cnt;
          r[j] = pos[i][goal] % val;
        }
      }
    }
    for (size_t i = 0; i < primes.size(); i++) {
      prod *= modpow(primes[i], pot[i]);
    }
    if (!ok) continue;
    for (size_t i = 0; i < primes.size(); i++) {
      if (pot[i] == 0) continue;
      int mod = modpow(primes[i], pot[i]);
      cur += ((prod / mod) * r[i] % prod) *
          modinv((int) ((prod / mod) % mod), primes[i], pot[i], mod);
      cur %= prod;
    }
    if (id == -1 || cur < ans) {
      id = goal;
      ans = cur;
    }
  }
  if (id == -1) printf("*\n");
  else cout << (id + 1) << " " << (ans + m) << endl;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
  long long val;
  scanf("%lld", &val);
  auto s = to_string(val);
  int id = -1;
  vector<int> cnt(10, 0);
  for (int i = 0; i < (int) s.size(); i++) {
    if (cnt[s[i] - '0'] == 2) {
      id = i;
      break;
    }
    cnt[s[i] - '0']++;
  }
  while (id >= 0) {
    int v = s[id] - '0' - 1;
    while (v >= 0 && cnt[v] == 2) v--;
    if (v == -1) {
      id--;
      cnt[s[id] - '0']--;
    } else {
      s[id] = char(v + '0');
      cnt[v]++;
      for (int i = id + 1; i < (int) s.size(); i++) {
        v = 9;
        while (cnt[v] == 2) v--;
        cnt[v]++;
        s[i] = char(v + '0');
      }
      id = -1;
    }
  }
  while (s[0] == '0') s = s.substr(1);
  printf("%s\n", s.c_str());
}

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  set<string> emails;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s, t;
    cin >> s;
    int id = (int) s.find('@');
    for (int j = 0; j < id; j++) {
      if (s[j] == '+') break;
      if (s[j] == '.') continue;
      t += s[j];
    }
    t += s.substr(id);
    emails.insert(t);
  }
  cout << emails.size() << endl;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
  double r;
  cin >> r;
  cout << 36000 / __gcd((int)round(r * 100), 36000) << endl;
}

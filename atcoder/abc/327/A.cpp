#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  bool ok = false;
  for (int i = 1; i < n; ++i) {
    ok |= (s[i - 1] == 'a' && s[i] == 'b') || (s[i - 1] == 'b' && s[i] == 'a');
  }
  std::cout << (ok ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
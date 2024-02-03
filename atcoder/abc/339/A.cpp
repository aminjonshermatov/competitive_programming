#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  for (int i = int(s.size()) - 1; i >= 0; --i) {
    if (s[i] == '.') {
      for (int j = i + 1; j < s.size(); ++j) {
        std::cout << s[j];
      }
      std::cout << '\n';
      return;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
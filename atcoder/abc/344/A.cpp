#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '|') {
      ++i;
      while (s[i] != '|') ++i;
    } else {
      std::cout << s[i];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
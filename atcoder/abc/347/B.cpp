#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  const auto n = int(s.size());
  std::set<std::string> ss;
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      ss.emplace(s.substr(i, j - i + 1));
    }
  }
  std::cout << ss.size() << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
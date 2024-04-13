#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  const auto n = int(s.size());
  std::array<int, 26> cnt{};
  for (auto c : s) {
    ++cnt[c - 'a'];
  }
  for (int i = 0; i < n; ++i) {
    int eq = 0;
    for (auto c : cnt) {
      eq += c == (i + 1);
    }
    if (eq != 0 && eq != 2) {
      std::cout << "No\n";
      return;
    }
  }
  std::cout << "Yes\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
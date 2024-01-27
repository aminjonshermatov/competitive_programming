#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  std::array<int, 26> cnt{};
  int max = 0;
  for (auto c : s) {
    max = std::max(max, ++cnt[c - 'a']);
  }
  for (int c = 0; c < 26; ++c) {
    if (cnt[c] == max) {
      std::cout << char('a' + c) << '\n';
      return;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  std::map<char, int> cnt{};
  for (auto c : s) {
    ++cnt[c];
  }
  for (auto [a, b] : cnt) {
    if (b == 1) {
      for (int i = 1; i <= s.size(); ++i) {
        if (s[i - 1] == a) {
          std::cout << i << '\n';
          return;
        }
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
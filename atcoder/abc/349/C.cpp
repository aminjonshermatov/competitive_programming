#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s, t;
  std::cin >> s >> t;
  for (auto& c : t) {
    c = std::tolower(c);
  }
  int ptr = 0;
  for (auto c : s) {
    if (ptr < 3 && t[ptr] == c) {
      ++ptr;
    }
  }
  std::cout << (ptr >= 3 || ptr == 2 && t[ptr] == 'x' ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
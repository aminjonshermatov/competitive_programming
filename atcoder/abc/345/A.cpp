#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::string s;
  std::cin >> s;
  std::cout << (s[0] == '<' && s.back() == '>' && std::all_of(s.begin() + 1, s.end() - 1, [](char c) { return c == '='; }) ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
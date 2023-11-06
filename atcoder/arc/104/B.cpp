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

  auto id = [](char c) -> int {
    return c == 'A' ? 0 : c == 'T' ? 1 : c == 'C' ? 2 : 3;
  };

  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    std::array<int, 4> f{};
    for (int j = i; j < n; ++j) {
      ++f[id(s[j])];
      cnt += f[0] == f[1] && f[2] == f[3];
    }
  }
  std::cout << cnt << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
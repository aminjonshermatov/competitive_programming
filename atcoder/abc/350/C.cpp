#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> ps(n), where(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> ps[i];
    where[--ps[i]] = i;
  }
  std::vector<std::pair<int, int>> ops;
  dbg(ps);
  for (int i = 0; i < n; ++i) {
    if (ps[i] == i) {
      continue;
    }
    auto j = where[i];
    ops.emplace_back(i, j);
    where[ps[i]] = j;
    ps[j] = ps[i];
  }
  std::cout << ops.size() << '\n';
  for (auto [i, j] : ops) {
    std::cout << i + 1 << ' ' << j + 1 << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
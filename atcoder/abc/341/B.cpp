#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using i64 = int64_t;
  int n;
  std::cin >> n;
  std::vector<i64> as(n);
  for (auto& a : as) {
    std::cin >> a;
  }
  for (int i = 0; i + 1 < n; ++i) {
    i64 s, t;
    std::cin >> s >> t;
    as[i + 1] += as[i] / s * t;
  }
  std::cout << as.back() << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
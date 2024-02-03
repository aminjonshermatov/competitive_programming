#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  using i64 = int64_t;
  i64 pf = 0, min = std::numeric_limits<i64>::max() / 2;
  for (int i = 0; i < n; ++i) {
    i64 x;
    std::cin >> x;
    pf += x;
    min = std::min(min, pf);
  }
  std::cout << pf + (min < 0 ? -min : 0) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
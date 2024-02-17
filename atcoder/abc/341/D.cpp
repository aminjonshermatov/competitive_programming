#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using u64 = uint64_t;
  u64 n, m, k;
  std::cin >> n >> m >> k;
  u64 lo = 0, hi = 1e18 + 10;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    auto nn = mid / n;
    auto mm = mid / m;
    auto nm = mid / std::lcm(n, m);
    (nn + mm - nm * 2 >= k ? hi : lo) = mid;
  }
  std::cout << hi << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
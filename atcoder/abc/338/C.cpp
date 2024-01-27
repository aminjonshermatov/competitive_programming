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
  std::vector<i64> qs(n), as(n), bs(n);
  for (auto& q : qs) {
    std::cin >> q;
  }
  for (auto& a : as) {
    std::cin >> a;
  }
  for (auto& b : bs) {
    std::cin >> b;
  }
  i64 best = 0;
  for (int x = 0; x <= 1e6; ++x) {
    bool ok = true;
    for (int i = 0; i < n && ok; ++i) {
      ok &= as[i] * x <= qs[i];
    }
    if (!ok) {
      break;
    }
    i64 y = 1e7;
    for (int i = 0; i < n; ++i) {
      i64 lo = 0, hi = 1e7;
      while (hi - lo > 1) {
        auto mid = lo + (hi - lo) / 2;
        (as[i] * x + bs[i] * mid <= qs[i] ? lo : hi) = mid;
      }
      y = std::min(y, lo);
    }
    best = std::max(best, x + y);
  }
  std::cout << best << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
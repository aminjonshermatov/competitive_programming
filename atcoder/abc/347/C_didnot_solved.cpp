#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using i64 = int64_t;
  int n;
  i64 a, b;
  std::cin >> n >> a >> b;
  std::vector<i64> as(n);
  for (auto& x : as) {
    std::cin >> x;
    x = x % (a + b);
    if (x < 0) {
      x += a + b;
    }
  }
  const auto [min, max] = std::ranges::minmax(as);
  std::cout << (max - min <= a ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

using ld = long double;
using i64 = int64_t;

i64 a, x, y;

std::map<i64, ld> cache;
ld E(i64 n) {
  if (n == 0) {
    return 0;
  }
  if (auto it = cache.find(n); it != cache.end()) {
    return it->second;
  }

  auto ret = x + E(n / a);
  ret = std::min(ret, (y * 6 + E(n / 2) + E(n / 3) + E(n / 4) + E(n / 5) + E(n / 6)) / 5);
  cache.emplace(n, ret);
  return ret;
}

void solve() {
  i64 n;
  std::cin >> n >> a >> x >> y;
  std::cout << std::fixed << std::setprecision(10) << E(n) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
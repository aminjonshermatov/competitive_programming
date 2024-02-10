#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;
std::map<i64, i64> cache;
i64 go(i64 x) {
  if (x < 2) {
    return 0;
  }
  if (cache.contains(x)) {
    return cache[x];
  }
  auto a = x / 2;
  return cache[x] = x + go(a) + go(x - a);
}

void solve() {
  i64 x;
  std::cin >> x;
  std::cout << go(x) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
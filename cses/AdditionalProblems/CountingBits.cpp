#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using i64 = int64_t;
  i64 n;
  std::cin >> n;
  bool seen[64][2];
  std::pair<i64, i64> cache[64][2];
  std::memset(seen, 0, sizeof seen);
  auto dfs = [&](auto& f, int pos, bool can_use_any) -> std::pair<i64, i64> {
    if (pos < 0) {
      return {0, 1};
    }
    if (seen[pos][can_use_any]) {
      return cache[pos][can_use_any];
    }
    i64 loc = 0, count = 0;
    auto c = n >> pos & 1;
    for (int d = 0; d <= (can_use_any ? 1 : c); ++d) {
      auto [val, cnt] = f(f, pos - 1, can_use_any || (d < c));
      loc += val + d * cnt;
      count += cnt;
    }
    seen[pos][can_use_any] = true;
    return cache[pos][can_use_any] = {loc, count};
  };
  std::cout << dfs(dfs, 63 - __builtin_clzll(n), false).first << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
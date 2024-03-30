#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using i64 = int64_t;
  int a, b;
  i64 c;
  std::cin >> a >> b >> c;
  int cache[62][62][62];
  int prv[62][62][62];
  std::memset(cache, -1, sizeof(cache));
  auto dfs = [&](auto&& self, int ib, int aa, int bb) -> bool {
    if (ib < 0) {
      return aa == 0 && bb == 0;
    }
    auto& loc = cache[ib][aa][bb];
    if (loc != -1) {
      return loc;
    }
    loc = 0;
    if (c >> ib & 1) {
      if (aa > 0 && self(self, ib - 1, aa - 1, bb)) {
        loc |= 1;
        prv[ib][aa][bb] = 1;
      }
      if (bb > 0 && self(self, ib - 1, aa, bb - 1)) {
        loc |= 1;
        prv[ib][aa][bb] = 2;
      }
      return loc;
    }
    if (aa > 0 && bb > 0 && self(self, ib - 1, aa - 1, bb - 1)) {
      loc |= 1;
      prv[ib][aa][bb] = 3;
    }
    if (self(self, ib - 1, aa, bb)) {
      loc |= 1;
      prv[ib][aa][bb] = 4;
    }
    return loc;
  };
  if (!dfs(dfs, 60, a, b)) {
    std::cout << -1 << '\n';
    return;
  }
  i64 x = 0, y = 0;
  for (int ib = 60; ib >= 0; --ib) {
    if (prv[ib][a][b] == 1) {
      x |= 1LL << ib;
      --a;
    } else if (prv[ib][a][b] == 2) {
      y |= 1LL << ib;
      --b;
    } else if (prv[ib][a][b] == 3) {
      x |= 1LL << ib;
      y |= 1LL << ib;
      --a, --b;
    }
  }
  std::cout << x << ' ' << y << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
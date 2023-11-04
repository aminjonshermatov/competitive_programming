#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  int n;
  std::cin >> n;
  std::vector<i64> as(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> as[i];
  }

  std::vector<i64> pf(n);
  for (int i = 0; i < n; ++i) {
    pf[i] = (i > 0 ? pf[i - 1] : 0) + as[i];
  }
  auto get = [&](int l, int r) -> i64 {
    assert(0 <= l && l <= r && r < n);
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };
  dbg(pf);

  constexpr auto inf = std::numeric_limits<i64>::max();
  std::vector cache(n, std::vector<i64>(n, -1));
  for (int i = 0; i < n; ++i) {
    cache[i][i] = 0;
  }
  auto dp = [&](auto &f, int l, int r) -> i64 {
    assert(0 <= l && l <= r && r < n);
    auto &loc = cache[l][r];
    if (loc != -1) return loc;
    loc = inf;

    for (int mid = l; mid < r; ++mid) {
      loc = std::min(loc, get(l, r) + f(f, l, mid) + f(f, mid + 1, r));
    }
    assert(loc != inf);
    return loc;
  };
  std::cout << dp(dp, 0, n - 1) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}

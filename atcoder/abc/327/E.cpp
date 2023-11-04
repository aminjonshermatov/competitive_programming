#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;
using ld = long double;

void solve() {
  int n;
  std::cin >> n;
  std::vector<i64> ps(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> ps[i];
  }

  using T = std::array<ld, 2>;
  std::vector<T> dp(n + 1, {-1, -1});
  dp[0] = {0, 0};

  auto f = [&](const T &a, int k) -> ld {
    return ld(a[0]) / a[1] - ld(1200) / std::sqrtl(k);
  };

  auto cmp = [&](const T &a, __int128 ka, const T &b, __int128 kb) -> bool {
    if (b[0] == -1) return true;
    return f(a, ka) > f(b, kb);
  };
  for (int i = 0; i < n; ++i) {
    auto ndp = dp;
    for (int x = 0; x <= n; ++x) {
      if (dp[x][0] == -1) continue;
      T nval = {dp[x][0] * .9 + ps[i], dp[x][1] * .9 + 1};
      dbg(i, x, nval);
      if (cmp(nval, x + 1, ndp[x + 1], x + 1)) {
        dbg("pk");
        ndp[x + 1] = nval;
      }
    }
    dp.swap(ndp);
  }
  ld ans = -1e15;
  for (auto &x : dp) {
    dbg(x);
  }
  for (int x = 1; x <= n; ++x) {
    ans = std::max(ans, f(dp[x], x));
    dbg(x, f(dp[x], x));
  }
  std::cout << std::fixed << std::setprecision(15) << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;
using i32 = int32_t;

constexpr auto inf = std::numeric_limits<i64>::max() / 2;
constexpr i32 N = 3002;
static i64 cs[N], pf[N], pfC[N], sf[N], sfC[N], cost[N][N], dp[2][N];
static i32 nxt;

inline i64 C(i32 l, i32 m, i32 r) {
  return pfC[m] - pfC[l - 1] - pf[l - 1] * (m - l + 1) + sfC[m] - sfC[r + 1] - sf[r + 1] * (r - m + 1);
}

inline void dnq(i32 l, i32 r, i32 opt_l, i32 opt_r) {
  if (l > r) {
    return;
  }
  auto mid = l + (r - l) / 2;
  i32 opt = opt_l;
  for (i32 x = opt_l; x <= std::min(opt_r, mid); ++x) {
    auto nval = dp[nxt ^ 1][x - 1] + cost[x][mid];
    if (nval < dp[nxt][mid]) {
      dp[nxt][mid] = nval;
      opt = x;
    }
  }
  dnq(l, mid - 1, opt_l, opt);
  dnq(mid + 1, r, opt, opt_r);
}

void solve() {
  i32 n, k;
  std::cin >> n >> k;

  for (i32 i = 1; i <= n; ++i) {
    std::cin >> cs[i];
  }

  pf[0] = pfC[0] = 0;
  for (i32 i = 1; i <= n; ++i) {
    pfC[i] = pfC[i - 1] + pf[i - 1];
    pf[i] = pf[i - 1] + cs[i];
  }
  sf[n + 1] = sfC[n + 1] = 0;
  for (i32 i = n; i > 0; --i) {
    sfC[i] = sfC[i + 1] + sf[i + 1];
    sf[i] = sf[i + 1] + cs[i];
  }

  for (i32 l = 1; l <= n; ++l) {
    i32 best_mid = l;
    for (i32 r = l; r <= n; ++r) {
      while (best_mid < r && C(l, best_mid, r) > C(l, best_mid + 1, r)) {
        ++best_mid;
      }
      cost[l][r] = C(l, best_mid, r);
    }
  }

  nxt = 1;
  std::fill(dp[nxt ^ 1], dp[nxt ^ 1] + n + 1, inf);
  dp[nxt ^ 1][0] = 0;
  for (i32 iter = 1; iter <= k; ++iter, nxt ^= 1) {
    std::fill(dp[nxt], dp[nxt] + n + 1, inf);
    dnq(1, n, 1, n);
  }
  std::cout << dp[nxt ^ 1][n] << '\n';
}

int32_t main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
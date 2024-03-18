#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;
constexpr auto inf = std::numeric_limits<i64>::max() / 2;

void solve() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> cs(n), vs(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> cs[i] >> vs[i];
  }

  std::vector<std::array<std::pair<int, i64>, 2>> dp(k + 1, {{{-1, -inf}, {-2, -inf}}});
  auto upd = [&](std::array<std::pair<int, i64>, 2>& to, std::pair<int, i64> target) {
    if (to[0].first == target.first) {
      to[0].second = std::max(to[0].second, target.second);
    } else if (to[1].first == target.first) {
      to[1].second = std::max(to[1].second, target.second);
      if (to[0].second < to[1].second) {
        std::swap(to[0], to[1]);
      }
    } else if (to[0].second < target.second) {
      to[1] = to[0];
      to[0] = target;
    } else if (to[1].second < target.second) {
      to[1] = target;
    }
    assert(to[0].first != to[1].first);
    assert(to[0].second >= to[1].second);
  };
  dp[0][0].second = 0;
  for (int i = 0; i < n; ++i) {
    decltype(dp) ndp(k + 1, {{{-1, -inf}, {-2, -inf}}});
    for (int j = 0; j <= k; ++j) {
      // remove
      if (j != k) {
        upd(ndp[j + 1], dp[j][0]);
        upd(ndp[j + 1], dp[j][1]);
      }

      // add
      if (dp[j][0].first != cs[i]) {
        upd(ndp[j], std::pair(cs[i], dp[j][0].second + vs[i]));
      } else {
        assert(dp[j][1].first != cs[i]);
        upd(ndp[j], std::pair(cs[i], dp[j][1].second + vs[i]));
      }
    }
    std::swap(ndp, dp);
  }
  std::cout << std::max<i64>(-1, dp[k][0].second) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
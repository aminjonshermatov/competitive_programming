#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;
struct Edge {
  int u, v;
  i64 w;
};

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<Edge> es(m);
  for (auto& [u, v, w] : es) {
    std::cin >> u >> v >> w;
    --u, --v;
  }
  constexpr auto inf = std::numeric_limits<i64>::max() / 2;
  std::vector dp(1 << n, std::vector<i64>(n, inf));
  for (int v = 0; v < n; ++v) {
    dp[1 << v][v] = 0;
  }
  for (int seen = 1; seen < (1 << n); ++seen) {
    bool any = true;
    for (int _ = 0; _ < n && any; ++_) {
      any = false;
      for (auto [u, v, w] : es) {
        if (dp[seen][u] == inf || (seen >> u & 1) == 0) {
          continue;
        }
        auto nw = dp[seen][u] + w;
        if (nw < dp[seen | (1 << v)][v]) {
          any |= true;
          dp[seen | (1 << v)][v] = nw;
        }
      }
    }
    assert(!any && "Detected cycle with negative weight");
  }
  auto best = std::ranges::min(dp[(1 << n) - 1]);
  if (best == inf) {
    std::cout << "No";
  } else {
    std::cout << best;
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
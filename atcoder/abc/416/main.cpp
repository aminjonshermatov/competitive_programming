#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n, k;
  Scan(n, k);
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;

    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  // dp[u][k] max= dp[v][k_i] + path[v] - path[u], v in subtree of u, sum(k_i)=k
  std::vector tin(n, 0), tout(n, 0);
  std::vector path(n, int64_t{0});
  auto timer = 0;
  auto dfs = [&](auto&& self, int v, int fa) -> void {
    tin[v] = timer++;
    path[v] += as[v];
    if (fa != -1) {
      path[v] += path[fa];
    }
    for (auto u : g[v]) {
      if (u != fa) {
        self(self, u, v);
      }
    }
    tout[v] = timer;
  };
  dfs(dfs, 0, -1);

  auto ret = int64_t{0};
  auto dp = [&](auto&& self, int v, int fa) -> std::vector<int64_t> {
    std::vector dp(k + 1, int64_t{0});
    dp[1] = fa != -1 ? path[v] : 0;
    for (auto u : g[v]) {
      if (u != fa) {
        const auto sub = self(self, u, v);
        for (int x = 0; x <= k; ++x) {
          ret = std::max(ret, sub[x] - path[v]);
        }
        for (int a = 0; a <= k; ++a) {
          for (int b = 0; b <= k; ++b) {
            ret = std::max(ret, sub[a] + dp[b] - path[v]);
          }
        }
        for (int me = k; me >= 0; --me) {
          for (int oth = 0; oth <= k; ++oth) {
            if (me + oth <= k) {
              dp[me + oth] = std::max(dp[me + oth], dp[me] + sub[oth]);
            }
          }
        }
      }
    }
    dbg(v,dp);
    return dp;
  };
  [[maybe_unused]] auto _ = dp(dp, 0, -1);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);


  Solve();
}

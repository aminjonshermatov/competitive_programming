#include <bits/stdc++.h>
#include <execution>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, k;
  std::cin >> n >> k;
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  std::vector<int> size(n, 0);
  std::vector<bool> died(n, false);
  auto dfs_sz = [&](auto& f, int v, int p) -> int {
    size[v] = 1;
    for (auto u : g[v]) {
      if (u != p && !died[u]) {
        size[v] += f(f, u, v);
      }
    }
    return size[v];
  };
  auto centroid = [&](auto& f, int v, int p, int sz) -> int {
    for (auto u : g[v]) {
      if (u != p && !died[u] && size[u] * 2 >= sz) {
        return f(f, u, v, sz);
      }
    }
    return v;
  };
  using i64 = int64_t;
  std::vector<i64> cnt(k + 1);
  auto dfs_calc = [&](auto& f, int v, int p, int depth, int& max_depth, bool do_update) -> i64 {
    if (depth > k) {
      return 0;
    }
    i64 loc = 0;
    max_depth = std::max(max_depth, depth);
    if (do_update) {
      ++cnt[depth];
    } else {
      loc += cnt[k - depth];
    }
    for (auto u : g[v]) {
      if (u != p && !died[u]) {
        loc += f(f, u, v, depth + 1, max_depth, do_update);
      }
    }
    return loc;
  };
  auto cd = [&](auto& f, int v, int p) -> i64 {
    auto c = centroid(centroid, v, p, dfs_sz(dfs_sz, v, p));
    died[c] = true;
    cnt[0] = 1;
    i64 loc = 0;
    int max_depth = 0;
    for (auto u : g[c]) {
      if (u != p && !died[u]) {
        loc += dfs_calc(dfs_calc, u, c, 1, max_depth, false);
        assert(dfs_calc(dfs_calc, u, c, 1, max_depth, true) == 0);
      }
    }
    std::fill(std::execution::par_unseq, cnt.begin(), cnt.begin() + max_depth + 1, 0);
    for (auto u : g[c]) {
      if (u != p && !died[u]) {
        loc += f(f, u, c);
      }
    }
    return loc;
  };
  std::cout << cd(cd, 0, -1) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
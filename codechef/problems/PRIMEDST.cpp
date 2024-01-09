#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

decltype(auto) get_primes_till(int n) {
  std::vector<int> primes;
  std::vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int x = 2; x <= n; ++x) {
    if (!is_prime[x]) {
      continue;
    }
    primes.emplace_back(x);
    for (int y = x * 2; y <= n; y += x) {
      is_prime[y] = false;
    }
  }
  return primes;
}

void solve() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  std::vector<int> size(n);
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
  auto centroid = [&](auto& f, int v, int p, int desired) -> int {
    for (auto u : g[v]) {
      if (u != p && !died[u] && size[u] >= desired) {
        return f(f, u, v, desired);
      }
    }
    return v;
  };

  using i64 = int64_t;
  auto primes = get_primes_till(n);
  std::vector<int> cnt(n + 1, 0);
  auto dfs_calc = [&](auto& f, int v, int p, int depth, int& max_depth, bool do_update) -> i64 {
    i64 loc = 0;
    max_depth = std::max(max_depth, depth);
    if (do_update) {
      ++cnt[depth];
    } else {
      for (auto it = std::lower_bound(primes.begin(), primes.end(), depth); it != primes.end(); ++it) {
        loc += cnt[*it - depth];
      }
    }
    for (auto u : g[v]) {
      if (u != p && !died[u]) {
        loc += f(f, u, v, depth + 1, max_depth, do_update);
      }
    }
    return loc;
  };
  auto CD = [&](auto& f, int v, int p) -> i64 {
    auto c = centroid(centroid, v, p, dfs_sz(dfs_sz, v, p) / 2);
    died[c] = true;
    i64 loc = 0;
    int max_depth = 0;
    for (auto u : g[c]) {
      if (!died[u]) {
        loc += dfs_calc(dfs_calc, u, c, 1, max_depth, false);
        assert(dfs_calc(dfs_calc, u, c, 1, max_depth, true) == 0);
      }
    }
    std::fill(cnt.begin() + 1, cnt.begin() + max_depth + 1, 0);
    for (auto u : g[c]) {
      if (!died[u]) {
        loc += f(f, u, c);
      }
    }
    return loc;
  };
  cnt[0] = 1;
  using f80 = long double;
  std::cout << std::fixed << std::setprecision(12) << f80(CD(CD, 0, -1) * 2) / (i64(n) * (n - 1)) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
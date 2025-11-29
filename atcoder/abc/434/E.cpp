#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

// Maximum matching in bipartite graph
// Kuhn's Algorithm
template <typename G>
decltype(auto) MaximumMatchingBipartite(int nA, int nB, G& g) {
  std::vector<int> mt(nB, -1), tm(nA, -1), when(nA, 0);

  int timer = 0;
  const auto tryKuhn = [&](auto &f, int v) -> bool {
    if (when[v] == timer) {
      return false;
    }
    when[v] = timer;
    for (auto u : g[v]) {
      if (mt[u] == -1) {
        tm[v] = u;
        mt[u] = v;
        return true;
      }
    }
    for (auto u : g[v]) {
      if (mt[u] != -1 && f(f, mt[u])) {
        tm[v] = u;
        mt[u] = v;
        return true;
      }
    }
    return false;
  };

  std::mt19937 mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
  for (int v = 0; v < nA; ++v) {
    std::shuffle(g[v].begin(), g[v].end(), mt19937);
  }

  for (bool run = true; run;) {
    run = false;
    ++timer;
    for (int v = 0; v < nA; ++v) {
      if (tm[v] == -1 && tryKuhn(tryKuhn, v)) {
        run = true;
      }
    }
  }

  std::vector<std::pair<int, int>> edges;
  for (int v = 0; v < nB; ++v) {
    if (mt[v] != -1) {
      edges.emplace_back(mt[v], v);
    }
  }
  return edges;
}

void Solve() {
  int n;
  Scan(n);
  std::vector<int> xs(n), rs(n);
  std::vector<int> all;
  all.reserve(n * 2);
  for (int i = 0; i < n; ++i) {
    Scan(xs[i], rs[i]);
    all.emplace_back(xs[i] - rs[i]);
    all.emplace_back(xs[i] + rs[i]);
  }

  std::ranges::sort(all);
  all.erase(std::ranges::unique(all).begin(), all.end());
  const auto m = int(all.size());

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    g[i].emplace_back(std::ranges::lower_bound(all, xs[i] - rs[i]) - all.begin());
    g[i].emplace_back(std::ranges::lower_bound(all, xs[i] + rs[i]) - all.begin());
  }
  Println(MaximumMatchingBipartite(n, m, g).size());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

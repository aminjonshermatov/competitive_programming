#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n;
  scan(n);
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  std::vector<int> sub(n, 0);
  auto dfs_pendant_size = [&](auto&& self, int v, int p) -> int {
    sub[v] = 0;
    if (g[v].size() == 1u) {
      return sub[v] = 1;
    }
    for (auto u : g[v]) {
      if (u == p) {
        continue;
      }
      self(self, u, v);
      sub[v] += sub[u];
    }
    return sub[v];
  };
  auto dfs_pendant_centroid = [&](auto&& self, int v, int p, int desired) -> int {
    for (auto u : g[v]) {
      if (u != p && g[u].size() > 1u && sub[u] >= desired) {
        return self(self, u, v, desired);
      }
    }
    return v;
  };

  const auto ids_view = std::views::iota(0, n);
  const auto first_non_pendant = *std::ranges::find_if(ids_view,
                                                       [&](auto&& v) { return g[v].size() > 1u; });
  const auto pendant_centroid = dfs_pendant_centroid(dfs_pendant_centroid, first_non_pendant, -1,
                                                     (dfs_pendant_size(dfs_pendant_size, first_non_pendant, -1) + 1) / 2);
  dfs_pendant_size(dfs_pendant_size, pendant_centroid, -1);
  std::map<int, std::vector<int>> nodes;
  auto dfs_collect_leafs = [&](auto&& self, int v, int p, int id) -> void {
    if (g[v].size() == 1u) {
      nodes[id].emplace_back(v);
      return;
    }
    for (auto u : g[v]) {
      if (u != p) {
        self(self, u, v, id);
      }
    }
  };
  std::priority_queue<std::pair<int, int>> pq;
  for (auto&& v : g[pendant_centroid]) {
    pq.emplace(sub[v], v);
    dfs_collect_leafs(dfs_collect_leafs, v, pendant_centroid, v);
  }
  std::vector<std::pair<int, int>> ops;
  while (pq.size() > 1) {
    const auto [sz1, root1] = pq.top(); pq.pop();
    const auto [sz2, root2] = pq.top(); pq.pop();
    ops.emplace_back(nodes[root1].back(), nodes[root2].back());
    nodes[root1].pop_back();
    if (!nodes[root1].empty()) {
      pq.emplace(sz1 - 1, root1);
    }
    nodes[root2].pop_back();
    if (!nodes[root2].empty()) {
      pq.emplace(sz2 - 1, root2);
    }
  }
  if (!pq.empty()) {
    const auto [_, root] = pq.top();
    pq.pop();
    ops.emplace_back(pendant_centroid, nodes[root].back());
  }
  println(ops.size());
  for (auto&& [i, j] : ops) {
    println(i + 1, j + 1);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
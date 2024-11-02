#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct DSU {
  int n, components;
  std::vector<int> parent, rank;

  explicit DSU(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  [[nodiscard]] int find(int v) noexcept {
    assert(0 <= v && v < n);

    while (v != parent[v]) {
      v = parent[v] = parent[parent[v]];
    }
    return v;
  }

  bool merge(int u, int v) noexcept {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    auto pu = find(u);
    auto pv = find(v);
    if (pu == pv) {
      return false;
    }

    if (rank[pu] < rank[pv]) {
      std::swap(pu, pv);
    }
    parent[pv] = pu;
    rank[pu] += rank[pv];
    --components;
    return true;
  }

  [[nodiscard]] bool is_same(int u, int v) noexcept {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
  }
};

void solve() {
  int n;
  scan(n);
  std::vector<int> deg(n);
  std::vector<std::pair<int, int>> es(n - 1);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scan(u, v);
    ++deg[--u];
    ++deg[--v];
    es[i - 1] = std::pair(u, v);
  }
  DSU dsu(n);
  std::vector<int> deg2(n);
  for (auto [u, v] : es) {
    if (deg[u] == 3 && deg[v] == 3) {
      dsu.merge(u, v);
    } else if (deg[u] == 3 && deg[v] == 2) {
      ++deg2[v];
    } else if (deg[v] == 3 && deg[u] == 2) {
      ++deg2[u];
    }
  }
  for (int i = 0; i < n; ++i) {
    dsu.find(i);
  }
  std::vector<std::vector<int>> adj(n);
  for (auto [u, v] : es) {
    if (deg[u] == 3 && deg[v] == 2) {
      adj[dsu.find(u)].emplace_back(v);
    }
    if (deg[v] == 3 && deg[u] == 2) {
      adj[dsu.find(v)].emplace_back(u);
    }
  }
  dbg(deg2);
  using i64 = int64_t;
  i64 tot = 0;
  std::vector<i64> tot2(n);
  for (auto& vs: adj) {
    tot += (static_cast<i64>(vs.size()) - 1) * 1LL * vs.size() / 2;
  }

  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
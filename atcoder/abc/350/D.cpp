#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

struct DSU {
  int n, components;
  std::vector<int> parent, rank;

  explicit DSU(int n_) : n(n_), components(n), parent(n), rank(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  inline int find(int v) {
    assert(0 <= v && v < n);

    while (v != parent[v]) {
      v = parent[v] = parent[parent[v]];
    }
    return v;
  }

  bool merge(int u, int v) {
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

  inline bool is_same(int u, int v) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    return find(u) == find(v);
  }
};

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> es(m);
  DSU dsu(n);
  for (auto& [u, v] : es) {
    std::cin >> u >> v;
    --u, --v;
    dsu.merge(u, v);
  }
  std::map<int, int> cnt{};
  for (auto [u, v] : es) {
    ++cnt[dsu.find(u)];
  }
  int64_t tot = 0;
  for (auto [c, x] : cnt) {
    const auto y = dsu.rank[c];
    tot += y * 1LL * (y - 1) / 2 - x;
  }
  std::cout << tot << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
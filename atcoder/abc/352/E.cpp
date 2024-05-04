#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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
  scan(n, m);
  std::vector<std::pair<int, std::vector<int>>> ops(m);
  for (int i = 0; i < m; ++i) {
    int k, c;
    scan(k, c);
    ops[i].first = c;
    ops[i].second.resize(k);
    for (auto&& v : ops[i].second) {
      scan(v);
      --v;
    }
  }
  std::vector<int> ord(m);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return ops[i].first < ops[j].first;
  });

  using i64 = int64_t;
  i64 w = 0;
  DSU dsu(n);
  for (auto&& i : ord) {
    for (std::size_t j{1}; j < ops[i].second.size(); ++j) {
      if (dsu.merge(ops[i].second[0], ops[i].second[j])) {
        w += ops[i].first;
      }
    }
  }
  println(dsu.components == 1 ? w : -1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
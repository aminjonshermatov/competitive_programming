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
  int n, m, y;
  scan(n, m, y);
  std::vector g(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scan(g[i][j]);
    }
  }

  auto id = [n, m](int i, int j) {
    return i * m + j;
  };
  auto parse = [m](int id) {
    auto [i, j] = std::div(id, m);
    return std::pair{i, j};
  };
  std::vector<int> ord(n * m);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int a, int b) {
    auto&& [ai, aj] = parse(a);
    auto&& [bi, bj] = parse(b);
    return g[ai][aj] < g[bi][bj];
  });

  std::array dk{1, 0, -1, 0, 1};
  auto ok = [n, m](int i, int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };

  DSU dsu(n * m + 1);
  const auto sea = n * m;
  std::vector<int> ret(y + 1);
  for (int h = 1, ptr{}; h <= y; ++h) {
    while (ptr < std::ssize(ord)) {
      const auto [i, j] = parse(ord[ptr]);
      if (g[i][j] > h) {
        break;
      }
      for (int k = 0; k < 4; ++k) {
        const auto ni = i + dk[k];
        const auto nj = j + dk[k + 1];
        if (!ok(ni, nj)) {
          dsu.merge(id(i, j), sea);
        } else if (g[ni][nj] <= h) {
          dsu.merge(id(i, j), id(ni, nj));
        }
      }
      ++ptr;
    }
    ret[h] = n * m - dsu.rank[dsu.find(sea)] + 1;
  }

  for (int i = 1; i <= y; ++i) {
    print(ret[i]);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}
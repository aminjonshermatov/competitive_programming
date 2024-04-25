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

inline int reduce(auto&& a, auto&& mod) noexcept {
  if (a >= mod) {
    a %= mod;
  }
  if (a < 0) {
    a += mod;
  }
  return a;
}

constexpr int mod = 998244353, M = 800;

void solve() {
  int n, q;
  scan(n, q);

  std::vector<std::vector<int>> g(n + 1);
  std::vector<std::unordered_set<int>> adj(n + 1);
  DSU dsu(n + 1);

  std::vector<std::pair<int, int>> lazy;

  std::vector<int> par(n + 1);
  std::iota(par.begin(), par.end(), 0);

  auto recalc = [&]() {
    std::iota(par.begin(), par.end(), 0);
    std::vector<bool> used(n, false);
    for (int i = 1; i <= n; ++i) {
      if (used[i]) {
        continue;
      }
      std::queue<int> q;
      q.emplace(i);
      used[i] = true;
      while (!q.empty()) {
        const auto v = q.front();
        q.pop();
        for (const auto u : g[v]) {
          if (used[u]) {
            continue;
          }
          used[u] = true;
          par[u] = v;
          q.emplace(u);
        }
      }
    }
    lazy.clear();
  };

  int X = 0;
  while (q-- > 0) {
    int a, b, c;
    scan(a, b, c);

    const auto A = 1 + reduce(reduce(a * 1LL * (1 + X), mod), 2);
    const auto B = 1 + reduce(reduce(b * 1LL * (1 + X), mod), n);
    const auto C = 1 + reduce(reduce(c * 1LL * (1 + X), mod), n);

    if (A == 1) {
      adj[B].emplace(C);
      adj[C].emplace(B);
      g[B].emplace_back(C);
      g[C].emplace_back(B);
      dsu.merge(B, C);

      lazy.emplace_back(B, C);
      if (lazy.size() == M) {
        recalc();
      }
    } else {
      std::set<int> cand;
      if (dsu.is_same(B, C)) {
        cand.emplace(par[B]);
        cand.emplace(par[C]);
      }
      for (const auto [x, y] : lazy) {
        if (x == B || x == C) {
          cand.emplace(y);
        }
        if (y == B || y == C) {
          cand.emplace(x);
        }
      }
      X = 0;
      for (const auto x : cand) {
        if (!adj[B].contains(x) || !adj[C].contains(x)) {
          continue;
        }
        X = x;
      }
      println(X);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
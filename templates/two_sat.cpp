//
// Created by aminjon on 5/14/24.
//
#include <bits/stdc++.h>

struct TwoSat {
  explicit TwoSat(int nVariables) : n(nVariables), g(2 * n), rg(2 * n) { }

  // (a = fA) or (b = fB)
  void addClause(int a, bool fA, int b, bool fB) {
    // !a -> b
    addEdge(2 * a + !fA, 2 * b + fB);
    // !b -> a
    addEdge(2 * b + !fB, 2 * a + fA);
  }

  [[nodiscard]] std::optional<std::vector<bool>> solve() const {
    std::vector<bool> used(2 * n, false);
    std::vector<int> ord;
    ord.reserve(2 * n);
    auto dfsOrd = [&](auto&& self, int v) -> void {
      used[v] = true;
      for (auto&& u : g[v]) {
        if (!used[u]) {
          self(self, u);
        }
      }
      ord.emplace_back(v);
    };
    for (int v = 0; v < 2 * n; ++v) {
      if (!used[v]) {
        dfsOrd(dfsOrd, v);
      }
    }
    std::vector<int> comp(2 * n);
    std::fill(used.begin(), used.end(), false);
    auto dfs = [&](auto&& self, int v, int c) -> void {
      used[v] = true;
      comp[v] = c;
      for (auto&& u : rg[v]) {
        if (!used[u]) {
          self(self, u, c);
        }
      }
    };
    for (auto c = 0; auto&& v : ord | std::views::reverse) {
      if (!used[v]) {
        dfs(dfs, v, c++);
      }
    }
    std::vector<bool> sat(n);
    for (int v = 0; v < n; ++v) {
      if (comp[2 * v] == comp[2 * v + 1]) {
        return std::nullopt;
      }
      sat[v] = comp[2 * v] < comp[2 * v + 1];
    }
    return std::move(sat);
  }
private:
  int n;
  std::vector<std::vector<int>> g, rg;

  void addEdge(int a, int b) {
    assert(0 <= a && a < 2 * n);
    assert(0 <= b && b < 2 * n);
    g[a].emplace_back(b);
    rg[b].emplace_back(a);
  }
};
//
// Created by aminjon on 4/13/23.
//
#include <bits/stdc++.h>
#include "constants.h"

using namespace std;

int main() {
  ifstream in(constants::DATA_IN);
  ofstream out(constants::SLOW_OUT);

  int n, q; in >> n >> q;
  vector<int> A(n);
  for (auto &a : A) in >> a;

  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v; in >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  const int LG = 31 - __builtin_clz(n);
  vector<vector<int>> up(n, vector<int>(LG + 1, -1));
  vector<int> tin(n), tout(n);
  int timer = 0;
  auto dfs = [&](auto f, int v, int p) -> void {
    up[v][0] = p;
    for (int l = 1; l <= LG && ~up[v][l - 1]; ++l) {
      up[v][l] = up[up[v][l - 1]][l - 1];
    }
    tin[v] = timer++;
    for (auto u : g[v]) {
      if (u == p) continue ;
      f(f, u, v);
    }
    tout[v] = timer++;
  };
  dfs(dfs, 0, -1);

  auto is_accessor = [&](int u, int v) -> bool {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  };
  auto get_lca = [&](int u, int v) -> int {
    if (is_accessor(u, v)) return u;
    if (is_accessor(v, u)) return v;
    for (int l = LG; ~l; --l) {
      if (up[u][l] == -1) continue ;
      if (!is_accessor(up[u][l], v)) u = up[u][l];
    }
    return up[u][0];
  };

  for (int i = 0; i < q; ++i) {
    int u, v, k;
    in >> u >> v >> k;
    --u, --v;
    if (tin[u] > tin[v]) swap(u, v);

    auto lca = get_lca(u, v);
    vector<int> vs;
    while (u != lca) {
      vs.emplace_back(A[u]);
      u = up[u][0];
    }
    while (v != lca) {
      vs.emplace_back(A[v]);
      v = up[v][0];
    }
    vs.emplace_back(A[lca]);
    sort(vs.begin(), vs.end());
    out << vs[k - 1] << '\n';
  }
}
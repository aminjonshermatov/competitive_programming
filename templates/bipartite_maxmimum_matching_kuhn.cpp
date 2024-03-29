//
// Created by aminjon on 1/9/23.
//
#include <bits/stdc++.h>

// Maximum matching in bipartite graph
// Kuhn's Algorithm
template <typename G>
decltype(auto) MaximumMatchingBipartite(int nA, int nB, G& g) {
  std::vector<int> mt(nB, -1), tm(nA, -1), when(nA, 0);

  int timer = 0;
  const auto try_kuhn = [&](auto &f, int v) -> bool {
    if (when[v] == timer) return false;
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
      if (tm[v] == -1 && try_kuhn(try_kuhn, v)) {
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

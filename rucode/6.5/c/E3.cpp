#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

// Maximum matching in bipartite graph
// Kuhn's Algorithm
template <typename G>
decltype(auto) MaximumMatchingBipartite(int nA, int nB, const G& g) {
  vector<int> mt(nB, -1), tm(nA, -1), when(nA, 0);

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

  for (bool run = true; run;) {
    run = false;
    ++timer;
    for (int v = 0; v < nA; ++v) {
      if (tm[v] == -1 && try_kuhn(try_kuhn, v)) {
        run = true;
      }
    }
  }

  vector<pair<int, int>> edges;
  for (int v = 0; v < nB; ++v) {
    if (mt[v] != -1) {
      edges.emplace_back(mt[v], v);
    }
  }
  return edges;
}

void solve() {
  int n, k;
  cin >> n >> k;

  vector<vector<int>> g(n);
  for (int i = 0; i < n * k; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
  }

  for (auto [u, v] : MaximumMatchingBipartite(n, n, g)) {
    cout << u + 1 << ' ' << v + 1 << '\n';
  }
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

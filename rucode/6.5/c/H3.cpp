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

using i64 = int64_t;

void solve() {
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  vector<string> g(n);
  i64 tot = 0;
  for (auto &r : g) {
    cin >> r;
    tot += count(r.begin(), r.end(), '*');
  }

  if (b * 2 <= a) {
    cout << tot * b << '\n';
    return;
  }

  const auto ok = [&](int i, int j) -> bool {
    return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j;
  };

  constexpr array dk{1, 0, -1, 0, 1};
  vector<vector<int>> A(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] != '*' || (i + j) % 2 == 1) continue;
      for (int k = 0; k < 4; ++k) {
        auto ni = i + dk[k];
        auto nj = j + dk[k + 1];
        if (!ok(ni, nj) || g[ni][nj] != '*') continue;
        A[i * m + j].emplace_back(ni * m + nj);
      }
    }
  }
  i64 len = MaximumMatchingBipartite(n * m, n * m, A).size();
  cout << len * a + (tot - len * 2) * b << '\n';
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m, Q; cin >> n >> m >> Q;
  vector<vector<int>> g(n), ig(n);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    ig[v].emplace_back(u);
  }
  vector<bool> used(n, false);
  vector<int> ord;
  ord.reserve(n);
  auto dfs_ord = [&](auto &f, int v) -> void {
    used[v] = true;
    for (auto u : g[v]) {
      if (!used[u]) {
        f(f, u);
      }
    }
    ord.emplace_back(v);
  };
  for (int v = 0; v < n; ++v) {
    if (!used[v]) {
      dfs_ord(dfs_ord, v);
    }
  }
  vector<int> comp(n);
  auto dfs = [&](auto &f, int v, int c) -> void {
    comp[v] = c;
    used[v] = true;
    for (auto u : ig[v]) {
      if (!used[u]) {
        f(f, u, c);
      }
    }
  };
  int c = 0;
  reverse(ord.begin(), ord.end());
  fill(used.begin(), used.end(), false);
  for (auto v : ord) {
    if (!used[v]) {
      dfs(dfs, v, c++);
    }
  }
  vector<vector<int>> cig(c);
  vector<int> cdeg(c, 0);
  for (int v = 0; v < n; ++v) {
    for (auto u : g[v]) {
      if (comp[v] != comp[u]) {
        cig[comp[u]].emplace_back(comp[v]);
        ++cdeg[comp[v]];
      }
    }
  }

  used.assign(c, false);
  queue<int> q;
  for (int cc = 0; cc < c; ++cc) {
    if (cdeg[cc] == 0) {
      q.emplace(cc);
    }
  }
  constexpr int NAX = 5e4;
  vector<bitset<NAX>> can_reach(c);
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    can_reach[v][v] = true;
    for (auto u : cig[v]) {
      can_reach[u] |= can_reach[v];
      if (--cdeg[u] == 0) {
        q.emplace(u);
      }
    }
  }

  while (Q--) {
    int u, v; cin >> u >> v;
    --u, --v;
    cout << (can_reach[comp[u]][comp[v]] ? "YES" : "NO") << '\n';
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

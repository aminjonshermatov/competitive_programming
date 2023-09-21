#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, a, b;
  cin >> n >> a >> b;
  --a, --b;
  vector<vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  if (a == b) {
    cout << "NO\n";
    return;
  }

  vector<int> col(n, 0), par(n, -1);
  int cyc_ptr = 0;
  vector<vector<int>> cycs;
  const auto dfs = [&](auto &f, int v, int p) -> void {
    if (col[v] == 2) {
      return;
    }

    if (col[v] == 1) {
      int cur = p;
      cycs.emplace_back();
      cycs.back().emplace_back(cur);

      while (cur != v) {
        cur = par[cur];
        assert(cur != -1);
        cycs.back().emplace_back(cur);
      }
      ++cyc_ptr;
      return;
    }
    par[v] = p;
    col[v] = 1;
    for (auto u : g[v]) {
      if (u == par[v]) {
        continue;
      }
      f(f, u, v);
    }
    col[v] = 2;
  };
  dfs(dfs, 0, -1);
  constexpr auto inf = numeric_limits<int>::max();
  const auto bfs = [&](int V) -> vector<int> {
    queue<int> q;
    vector<int> dist(n, inf);
    q.emplace(V);
    dist[V] = 0;
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      for (auto u : g[v]) {
        if (dist[u] != inf) continue;
        dist[u] = dist[v] + 1;
        q.emplace(u);
      }
    }
    return dist;
  };
  auto a_dist = bfs(a);
  auto b_dist = bfs(b);
  int mn = -1;
  for (auto &cyc : cycs) {
    if (std::count(cyc.begin(), cyc.end(), a) == 1 && std::count(cyc.begin(), cyc.end(), b) == 1) {
      cout << "YES\n";
      return;
    }
    for (auto v : cyc) {
      if (mn == -1 || b_dist[mn] > b_dist[v]) {
        mn = v;
      }
    }
  }
  cout << (b_dist[mn] < a_dist[mn] ? "YES" : "NO") << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct Dinic {
  using i64 = int64_t;

  struct FlowEdge {
    int u, v;
    i64 cap, flow;
    FlowEdge(int u_, int v_, i64 cap_) : u(u_), v(v_), cap(cap_), flow(0) { }
  };

  static constexpr auto inf = numeric_limits<i64>::max();
  vector<FlowEdge> edges;
  vector<vector<int>> g;
  int n, S, T;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n_, int S_, int T_) : n(n_), S(S_), T(T_) {
    g.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void add_edge(int u, int v, i64 cap) {
    g[u].emplace_back(edges.size());
    edges.emplace_back(u, v, cap);
    g[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0);
  }
  bool bfs() {
    while (!q.empty()) {
      auto u = q.front();
      q.pop();
      for (auto i : g[u]) {
        if (edges[i].cap - edges[i].flow < 1) continue;
        auto v = edges[i].v;
        if (level[v] != -1) continue;
        level[v] = level[u] + 1;
        q.emplace(v);
      }
    }
    return level[T] != -1;
  }
  i64 dfs(int u, i64 pushed) {
    if (pushed == 0 || u == T) {
      return pushed;
    }
    for (auto &pid = ptr[u]; pid < g[u].size(); ++pid) {
      auto i = g[u][pid];
      auto v = edges[i].v;
      if (level[u] + 1 != level[v] || edges[i].cap - edges[i].flow < 1) continue;
      auto f = dfs(v, min(pushed, edges[i].cap - edges[i].flow));
      if (f == 0) continue;
      edges[i].flow += f;
      edges[i ^ 1].flow -= f;
      return f;
    }
    return 0;
  }
  i64 flow() {
    i64 f = 0;
    for (;;) {
      fill(level.begin(), level.end(), -1);
      level[S] = 0;
      q.emplace(S);
      if (!bfs()) {
        break;
      }
      fill(ptr.begin(), ptr.end(), 0);
      while (auto pushed = dfs(S, inf)) {
        f += pushed;
      }
    }
    return f;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> g(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> g[i][j];
      --g[i][j];
    }
  }

  dbg(g);

  vector<vector<int>> ans;
  ans.reserve(n);
  for (int jj = 0; jj < m; ++jj) {
    Dinic mf(2 * n + 2, 2 * n, 2 * n + 1);
    for (int i = 0; i < n; ++i) {
      mf.add_edge(2 * n, i, 1);
      mf.add_edge(i + n, 2 * n + 1, 1);
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (g[i][j] != -1) {
          mf.add_edge(i, g[i][j] + n, 1);
        }
      }
    }

    if (mf.flow() != n) {
      cout << "No\n";
      return;
    }

    vector<int> tmp(n);
    for (int u = 0; u < n; ++u) {
      for (auto id : mf.g[u]) {
        auto v = mf.edges[id].v - n;
        if (mf.edges[id].flow == 1 && clamp(v, 0, n - 1) == v) {
          tmp[u] = v;
          break;
        }
      }
    }
    ans.emplace_back();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (tmp[i] == g[i][j]) {
          ans.back().emplace_back(g[i][j]);
          g[i][j] = -1;
          break;
        }
      }
    }
  }
  dbg(ans);
  cout << "Yes\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << ans[j][i] + 1 << ' ';
    }
    cout << '\n';
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

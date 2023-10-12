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

  decltype(auto) flow() {
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
    array<vector<int>, 2> vs{};
    if (f < 2) return tuple{false, vs};
    vector<bool> seen(n);
    const auto dfs_ = [&](auto &f, int u, i64 fl, bool which) -> i64 {
      seen[u] = true;
      if (fl == 0 || u == T) return fl;
      for (auto id : g[u]) {
        if (edges[id].flow <= 0) continue;
        auto v = edges[id].v;
        if (seen[v]) continue;
        vs[which].emplace_back(v);
        auto nfl = f(f, v, min(fl, edges[id].flow), which);
        if (nfl == 0) {
          vs[which].pop_back();
          continue;
        }
        edges[id].flow -= nfl;
        return nfl;
      }
      return 0;
    };

    for (int x = 0; x < 2; ++x) {
      fill(seen.begin(), seen.end(), false);
      vs[x].emplace_back(S);
      dfs_(dfs_, S, 1e9, x);
    }

    return tuple{true, vs};
  }
};

void solve() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  Dinic mf(n, s - 1, t - 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    mf.add_edge(u - 1, v - 1, 1);
  }
  auto [ok, vs] = mf.flow();
  if (!ok) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  for (auto &r : vs) {
    for (auto v : r) {
      cout << v + 1 << ' ';
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

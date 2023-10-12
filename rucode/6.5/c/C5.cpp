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
    int u, v, id;
    i64 cap, flow;
    FlowEdge(int u_, int v_, i64 cap_, int id_) : u(u_), v(v_), id(id_), cap(cap_), flow(0) { }
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
  void add_edge(int u, int v, i64 cap, int id) {
    g[u].emplace_back(edges.size());
    edges.emplace_back(u, v, cap, id);
    g[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0, -1);
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
    vector<pair<int, vector<int>>> decom;
    vector<bool> seen(n);
    const auto dfs_ = [&](auto &f, int u, i64 fl) -> int {
      seen[u] = true;
      if (u == T) return fl;
      if (fl == 0) return 0;
      for (auto id : g[u]) {
        if (edges[id].flow <= 0) continue;
        auto v = edges[id].v;
        if (seen[v]) continue;
        assert(!decom.empty());
        decom.back().second.emplace_back(edges[id].id);
        auto nfl = f(f, v, min(fl, edges[id].flow));
        if (nfl == 0) {
          decom.back().second.pop_back();
          continue;
        }
        edges[id].flow -= nfl;
        return nfl;
      }
      return 0;
    };
    for (;;) {
      decom.emplace_back();
      fill(seen.begin(), seen.end(), false);
      auto fl = dfs_(dfs_, S, 1e9);
      dbg(fl);
      if (fl == 0) {
        decom.pop_back();
        break;
      }
      decom.back().first = fl;
    }
    return decom;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Dinic mf(n, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    mf.add_edge(u - 1, v - 1, c, i);
  }
  auto decom = mf.flow();
  cout << decom.size() << '\n';
  for (auto &[f, es] : decom) {
    cout << f << ' ' << es.size() << ' ';
    for (auto i : es) {
      assert(i != -1);
      cout << i + 1 << ' ';
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

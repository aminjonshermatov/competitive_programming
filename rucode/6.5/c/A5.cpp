#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

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
      edges.emplace_back(v, u, cap, -1);
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
      vector<i64> fs(edges.size() >> 1);
      for (auto &e : edges) {
        if (e.id == -1) continue;
        fs[e.id] = e.flow;
      }
      return tuple{f, fs};
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
  auto [f, es] = mf.flow();
  cout << f << '\n';
  for (auto x : es) {
    cout << x << '\n';
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

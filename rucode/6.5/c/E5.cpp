#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

struct Dinic {
  using i64 = int;

  struct FlowEdge {
    char type;
    int u, v;
    i64 cap, flow;
    FlowEdge(int u_, int v_, i64 cap_, char type_) : u(u_), v(v_), cap(cap_), flow(0), type(type_) { }
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
  void add_edge(int u, int v, i64 cap, char type) {
    g[u].emplace_back(edges.size());
    edges.emplace_back(u, v, cap, type);
    g[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0, '?');
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
  decltype(auto) flow(int expected) {
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
    dbg(f);
    const auto nn = n - 28;
    array<vector<int>, 26> ids{};
    if (f != expected) return tuple{false, ids};
    const auto bfs_ = [&]() -> bool {
      while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto i : g[u]) {
          if (edges[i].flow <= 0) continue;
          auto v = edges[i].v;
          if (level[v] != -1) continue;
          level[v] = level[u] + 1;
          q.emplace(v);
        }
      }
      return level[T] != -1;
    };
    vector<int> when(n, 0);
    int timer = 0;
    const auto dfs_ = [&](auto &f, int u, i64 fl) -> i64 {
      when[u] = timer;
      if (fl == 0 || u == T) return fl;
      for (auto &pid = ptr[u]; pid < g[u].size(); ++pid) {
        auto id = g[u][pid];
        if (edges[id].flow <= 0) continue;
        auto v = edges[id].v;
        if (level[u] + 1 != level[v] || when[v] == timer) continue;
        bool ok = (edges[id].type == 'F' || edges[id].type == 'B') && clamp(u, 1, nn) == u && clamp(v, nn + 1, nn + 26) == v;
        if (ok) {
          ids[v - nn - 1].emplace_back(u * (edges[id].type == 'F' ? 1 : -1));
        }
        auto nfl = f(f, v, min(fl, edges[id].flow));
        if (nfl == 0) {
          if (ok) {
            ids[v - nn - 1].pop_back();
          }
          continue;
        }
        edges[id].flow -= nfl;
        return nfl;
      }
      return 0;
    };
    i64 ff = 0;
    for (;;) {
      fill(level.begin(), level.end(), -1);
      level[S] = 0;
      q.emplace(S);
      if (!bfs_()) {
        break;
      }
      ++timer;
      fill(ptr.begin(), ptr.end(), 0);
      while (auto pushed = dfs_(dfs_, S, inf)) {
        ff += pushed;
      }
    }
    assert(ff == f);
    return tuple{true, std::move(ids)};
  }
};

void solve() {
  int n;
  cin >> n;

  int S = 0, T = n + 27;
  Dinic mf(n + 28, S, T);
  for (int i = 1; i <= n; ++i) {
    char a, b;
    cin >> a >> b;
    mf.add_edge(S, i, 1, 'S');
    mf.add_edge(i, n + a - 'a' + 1, 1, 'F');
    mf.add_edge(i, n + b - 'a' + 1, 1, 'B');
  }
  string s;
  cin >> s;
  array<int, 26> cnt{};
  cnt.fill(0);
  for (auto c : s) {
    ++cnt[c - 'a'];
  }
  for (int c = 0; c < 26; ++c) {
    if (cnt[c] == 0) continue;
    mf.add_edge(n + c + 1, T, cnt[c], 'T');
  }

  auto [ok, ids] = mf.flow(s.size());
  if (!ok) {
    cout << "IMPOSSIBLE\n";
    return;
  }
  dbg(ids);
  for (auto c : s) {
    assert(!ids[c - 'a'].empty());
    cout << ids[c - 'a'].back() << ' ';
    ids[c - 'a'].pop_back();
  }
  cout << '\n';
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

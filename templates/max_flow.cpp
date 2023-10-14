#include <bits/stdc++.h>

using namespace std;

// Dinic's algorithm
struct MaxFlow {
    using i64 = int64_t;
    static constexpr auto inf = numeric_limits<i64>::max();

    struct FlowEdge {
        int u, v;
        i64 cap, flow;
        int id;
        FlowEdge(int u_, int v_, i64 cap_, int id_) : u(u_), v(v_), cap(cap_), flow(0), id(id_) { }
    };

    vector<FlowEdge> edges;
    vector<vector<int>> g;
    int n;
    vector<int> level, ptr;

    MaxFlow(int n_) : n(n_) {
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
    bool bfs(int S, int T) {
      queue<int> q;
      fill(level.begin(), level.end(), -1);
      level[S] = 0;
      q.emplace(S);
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
    i64 dfs(int u, int T, i64 pushed) {
      if (pushed == 0 || u == T) {
        return pushed;
      }
      for (auto &pid = ptr[u]; pid < g[u].size(); ++pid) {
        auto i = g[u][pid];
        auto v = edges[i].v;
        if (level[u] + 1 != level[v] || edges[i].cap - edges[i].flow < 1) continue;
        auto f = dfs(v, T, min(pushed, edges[i].cap - edges[i].flow));
        if (f == 0) continue;
        edges[i].flow += f;
        edges[i ^ 1].flow -= f;
        return f;
      }
      return 0;
    }

    decltype(auto) flow(int S, int T) {
      i64 f = 0;
      for (;;) {
        if (!bfs(S, T)) {
          break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (auto pushed = dfs(S, T, inf)) {
          f += pushed;
        }
      }
      map<int, i64> fall_through;
      for (const auto &edge : edges) {
        if (edge.id >= 0 && edge.flow > 0) {
          fall_through[edge.id] = edge.flow;
        }
      }
      return tuple{f, fall_through};
    }
};

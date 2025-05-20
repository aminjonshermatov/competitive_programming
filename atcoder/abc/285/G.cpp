#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

// Dinic's algorithm
template <std::integral FlowUnit = int64_t, bool DoDecompose = false>
struct MaxFlow {
  static constexpr auto inf = std::numeric_limits<FlowUnit>::max();

  struct FlowEdge {
    int u, v;
    FlowUnit cap, flow;
    int id;
    FlowEdge(int u_, int v_, FlowUnit cap_, int id_) : u(u_), v(v_), cap(cap_), flow(0), id(id_) { }
  };

  std::vector<FlowEdge> edges;
  std::vector<std::vector<int>> g;
  int n;
  std::vector<int> level, ptr;

  explicit MaxFlow(int n_) : n(n_) {
    g.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void addEdge(int u, int v, FlowUnit cap, int id = -1) {
    g[u].emplace_back(edges.size());
    edges.emplace_back(u, v, cap, id);
    g[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0, -1);
  }
  bool bfs(int S, int T) {
    std::queue<int> q;
    std::fill(level.begin(), level.end(), -1);
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
  FlowUnit dfs(int u, int T, FlowUnit pushed) {
    if (pushed == 0 || u == T) {
      return pushed;
    }
    for (auto &pid = ptr[u]; pid < g[u].size(); ++pid) {
      auto i = g[u][pid];
      auto v = edges[i].v;
      if (level[u] + 1 != level[v] || edges[i].cap - edges[i].flow < 1) continue;
      auto f = dfs(v, T, std::min(pushed, edges[i].cap - edges[i].flow));
      if (f == 0) continue;
      edges[i].flow += f;
      edges[i ^ 1].flow -= f;
      return f;
    }
    return 0;
  }

  decltype(auto) flow(int S, int T) {
    FlowUnit flow = 0;
    while (bfs(S, T)) {
      std::fill(ptr.begin(), ptr.end(), 0);
      while (auto pushed = dfs(S, T, inf)) {
        flow += pushed;
      }
    }
    if constexpr (DoDecompose) {
      std::map<int, FlowUnit> fall_through;
      for (const auto &edge : edges) {
        if (edge.id >= 0 && edge.flow > 0) {
          fall_through[edge.id] = edge.flow;
        }
      }
      return std::tuple{flow, fall_through};
    } else {
      return flow;
    }
  }
};

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector g(n, std::string{});
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  std::array dk{1, 0, -1, 0, 1};
  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };
  auto id = [m](const int i, const int j) {
    return i * m + j;
  };

  MaxFlow mf(n * m + 4);
  const auto s = n * m, t = s + 1, s2 = t + 1, t2 = s2 + 1;
  auto l2 = 0, r2 = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i % 2; j < m; j += 2) {
      if (g[i][j] == '2') {
        ++l2;
        mf.addEdge(s2, id(i, j), 1);
      } if (g[i][j] == '?') {
        mf.addEdge(s, id(i, j), 1);
      }
      for (int k = 0; k < 4; ++k) {
        const auto ni = i + dk[k];
        const auto nj = j + dk[k + 1];
        if (ok(ni, nj) && g[i][j] != '1' && g[ni][nj] != '1') {
          mf.addEdge(id(i, j), id(ni, nj), 1);
        }
      }
    }
    for (int j = 1 - i % 2; j < m; j += 2) {
      if (g[i][j] == '2') {
        ++r2;
        mf.addEdge(id(i, j), t2, 1);
      }
      if (g[i][j] == '?') {
        mf.addEdge(id(i, j), t, 1);
      }
    }
  }
  mf.addEdge(s, t2, l2);
  mf.addEdge(s2, t, r2);

  auto x = mf.flow(s2, t2);
  auto y = mf.flow(s, t2);
  auto z = mf.flow(s2, t);

  Println(x + y == l2 + r2 && x + z == l2 + r2 ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

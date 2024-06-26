#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

// Dinic's algorithm
template <std::integral FlowUnit = int64_t, bool DoDecompose = false>
struct MaxFlow {
  static constexpr auto inf = std::numeric_limits<FlowUnit>::max();

  struct FlowEdge {
    int u, v;
    FlowUnit cap, flow;
    int id;

    FlowEdge(int u_, int v_, FlowUnit cap_, int id_) : u(u_), v(v_), cap(cap_), flow(0),
                                                       id(id_) {}
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
      for (auto i: g[u]) {
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
    for (auto& pid = ptr[u]; pid < g[u].size(); ++pid) {
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
      for (const auto& edge: edges) {
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

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::vector<std::string> ss(n);
  std::vector<i64> as(n);
  for (auto&& s: ss) {
    scan(s);
  }
  for (auto&& a: as) {
    scan(a);
  }

  {
    std::map<std::string, i64> best;
    for (int i = 0; i < n; ++i) {
      best[ss[i]] = std::max(best[ss[i]], as[i]);
    }
    n = int(best.size());
    std::vector<std::pair<std::string, i64>> ps;
    ps.reserve(n);
    for (auto&& [s, a]: best) {
      ps.emplace_back(s, a);
    }
    std::ranges::sort(ps, [&](auto&& a, auto&& b) {
      return a.first.size() < b.first.size();
    });
    ss.clear();
    as.clear();
    for (auto&& [a, b]: ps) {
      ss.emplace_back(std::move(a));
      as.emplace_back(b);
    }
  }

  MaxFlow mf(2 * n + 2);
  const int S = 2 * n, T = S + 1;
  for (int i = 0; i < n; ++i) {
    mf.addEdge(S, 2 * i, as[i]);
    mf.addEdge(2 * i + 1, T, as[i]);
  }
  constexpr auto inf = std::numeric_limits<i64>::max() / 2;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (ss[i].contains(ss[j])) {
        mf.addEdge(2 * i, 2 * j + 1, inf);
      }
    }
  }
  println(
    std::ranges::fold_left(as, i64{}, [](auto&& acc, auto&& x) { return acc + x; }) -
    mf.flow(S, T));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
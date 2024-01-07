#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

template <std::integral FlowUnit = int64_t, std::integral CostUnit = int64_t, bool DoDecompose = false>
struct MinCostFlow {
  static constexpr auto inf = std::numeric_limits<CostUnit>::max();

  struct FlowEdge {
    int u, v;
    FlowUnit cap, flow;
    CostUnit cost;
    int id;
    FlowEdge(int u_, int v_, FlowUnit cap_, CostUnit cost_, int id_) : u(u_), v(v_), cap(cap_), flow{}, cost(cost_), id(id_) { }
  };

  int n;
  std::vector<std::vector<int>> g;
  std::vector<FlowEdge> edges;
  std::vector<CostUnit> pot, dist;
  std::vector<int> pre;
  explicit MinCostFlow(int n_) : n(n_) {
    g.resize(n);
    pot.resize(n);
    dist.resize(n);
    pre.resize(n);
  }
  void addEdge(int u, int v, FlowUnit cap, CostUnit cost, int id = -1) {
    g[u].emplace_back(edges.size());
    edges.emplace_back(u, v, cap, cost, id);
    g[v].emplace_back(edges.size());
    edges.emplace_back(v, u, 0, -cost, -1);
  }

  bool dijkstra(int S, int T) {
    dist.assign(n, inf);
    pre.assign(n, -1);

    std::priority_queue<std::pair<CostUnit, int>, std::vector<std::pair<CostUnit, int>>, std::greater<>> pq;
    pq.emplace(dist[S] = 0, S);
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d > dist[u]) {
        continue;
      }
      for (auto id : g[u]) {
        auto v = edges[id].v;
        if (edges[id].cap - edges[id].flow <= 0) {
          continue;
        }
        if (auto nd = d + edges[id].cost + pot[u] - pot[v]; nd < dist[v]) {
          dist[v] = nd;
          pre[v] = id;
          pq.emplace(dist[v] = nd, v);
        }
      }
    }
    return dist[T] != inf;
  }

  decltype(auto) flow(int S, int T, const FlowUnit flowLimit = inf) {
    std::fill(pot.begin(), pot.end(), CostUnit{});
    bool any = true;
    for (int _ = 0; _ < n && any; ++_) {
      any = false;
      for (const auto &edge : edges) {
        if (edge.cap == CostUnit{}) {
          continue;
        }
        if (auto npot = pot[edge.u] + edge.cost; pot[edge.v] > npot) {
          any |= true;
          pot[edge.v] = npot;
        }
      }
    }
    assert(!any && "Detected cycle with negative weight");

    FlowUnit flow{};
    CostUnit cost{};
    while (dijkstra(S, T) && flow < flowLimit) {
      for (int v = 0; v < n; ++v) {
        pot[v] += dist[v];
      }
      auto nf = flowLimit - flow;
      for (int v = T; v != S; v = edges[pre[v]].u) {
        nf = std::min(nf, edges[pre[v]].cap - edges[pre[v]].flow);
      }
      flow += nf;
      cost += (pot[T] - pot[S]) * nf;
      for (int v = T; v != S; v = edges[pre[v]].u) {
        edges[pre[v]].flow += nf;
        edges[pre[v] ^ 1].flow -= nf;
      }
    }
    if constexpr (DoDecompose) {
      //const auto mx_id = max_element(edges.begin(), edges.end(), [](const FlowEdge &lhs, const FlowEdge &rhs) {
      //  return lhs.id < rhs.id;
      //})->id;
      //std::vector<FlowUnit> fall_through(mx_id + 1, 0);
      std::map<int, FlowUnit> fall_through;
      for (const auto &edge : edges) {
        if (edge.id != -1 && edge.flow > 0) {
          fall_through[edge.id] = edge.flow;
        }
      }
      return std::tuple{flow, cost, std::move(fall_through)};
    } else {
      return std::tuple{flow, cost};
    }
  }
};

void solve() {
  int n;
  std::cin >> n;

  MinCostFlow<int, int, true> mcf(2 * n + 2);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int x;
      std::cin >> x;
      mcf.addEdge(i, n + j, 1, x, i * n + j);
    }
  }
  for (int i = 0; i < n; ++i) {
    mcf.addEdge(2 * n, i, 1, 0);
  }
  for (int j = 0; j < n; ++j) {
    mcf.addEdge(n + j, 2 * n + 1, 1, 0);
  }
  auto [f, c, fth] = mcf.flow(2 * n, 2 * n + 1);
  assert(f == n && fth.size() == n);
  std::cout << c << '\n';
  for (auto [k, _] : fth) {
    auto [i, j] = std::div(k, n);
    std::cout << i + 1 << ' ' << j + 1 << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
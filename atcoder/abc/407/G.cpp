#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <std::integral FlowUnit = int64_t, std::integral CostUnit = int64_t, bool DoDecompose = false>
class MinCostFlow {
 public:
 public:
  explicit MinCostFlow(const int n) : N_(n) {
    Graph_.resize(n);
    Potential_.resize(n);
    Distance_.resize(n);
    Previous_.resize(n);
  }

  auto AddEdge(int u, int v, FlowUnit capacity, CostUnit cost, int id = -1) {
    Graph_[u].emplace_back(Edges_.size());
    Edges_.emplace_back(u, v, capacity, cost, id);
    Graph_[v].emplace_back(Edges_.size());
    Edges_.emplace_back(v, u, 0, -cost, -1);
  }

  decltype(auto) Slope(const int s, const int t, const FlowUnit flowLimit = std::numeric_limits<FlowUnit>::max()) {
    std::ranges::fill(Potential_, CostUnit{});
    auto found = true;
    for ([[maybe_unused]] auto it = 0; it < N_ && found; ++it) {
      found = false;
      for (const auto& edge : Edges_) {
        if (edge.Capacity == CostUnit{}) {
          continue;
        }
        if (auto nPotential = Potential_[edge.U] + edge.Cost; Potential_[edge.V] > nPotential) {
          found |= true;
          Potential_[edge.V] = nPotential;
        }
      }
    }
    assert(!found && "Detected cycle with negative weight");

    std::vector<std::pair<FlowUnit, CostUnit>> results;
    FlowUnit flow{};
    CostUnit cost{};
    results.emplace_back(flow, cost);
    while (Dijkstra(s, t) && flow < flowLimit) {
      for (auto v = 0; v < N_; ++v) {
        Potential_[v] += Distance_[v];
      }
      std::integral auto nFlow = flowLimit - flow;
      for (auto v = t; v != s; v = Edges_[Previous_[v]].U) {
        nFlow = std::min(nFlow, Edges_[Previous_[v]].Capacity - Edges_[Previous_[v]].Flow);
      }
      flow += nFlow;
      cost += (Potential_[t] - Potential_[s]) * nFlow;
      if ((Potential_[t] - Potential_[s]) * nFlow == results.back().second) {
        results.pop_back();
      }
      results.emplace_back(flow, cost);
      for (auto v = t; v != s; v = Edges_[Previous_[v]].U) {
        Edges_[Previous_[v]].Flow += nFlow;
        Edges_[Previous_[v] ^ 1].Flow -= nFlow;
      }
    }
    if constexpr (DoDecompose) {
      std::map<int, FlowUnit> fallThrough;
      for (const auto& edge : Edges_) {
        if (edge.Id != -1 && edge.Flow > 0) {
          fallThrough[edge.Id] = edge.Flow;
        }
      }
      return std::tuple{std::move(results), std::move(fallThrough)};
    } else {
      return std::tuple{std::move(results)};
    }
  }

 private:
  auto Dijkstra(const int s, const int t) {
    Distance_.assign(N_, std::numeric_limits<CostUnit>::max());
    Previous_.assign(N_, -1);

    using T = std::tuple<CostUnit, int>;
    auto pq = std::priority_queue(std::greater<T>{}, std::vector<T>{});
    pq.emplace(Distance_[s] = 0, s);
    while (!pq.empty()) {
      const auto [d, u] = pq.top();
      pq.pop();
      if (d != Distance_[u]) {
        continue;
      }
      for (const auto id : Graph_[u]) {
        const auto v = Edges_[id].V;
        if (Edges_[id].Capacity - Edges_[id].Flow <= 0) {
          continue;
        }
        if (auto nD = d + Edges_[id].Cost + Potential_[u] - Potential_[v]; nD < Distance_[v]) {
          Previous_[v] = id;
          pq.emplace(Distance_[v] = nD, v);
        }
      }
    }
    return Distance_[t] != std::numeric_limits<CostUnit>::max();
  }

 private:
  struct FlowEdge {
    int U, V, Id;
    FlowUnit Capacity, Flow;
    CostUnit Cost;
    FlowEdge(int u, int v, FlowUnit capacity, CostUnit cost, int id)
      : U(u), V(v), Capacity(capacity), Flow{}, Cost(cost), Id(id)
    { }
  };

 private:
  int N_;
  std::vector<std::vector<int>> Graph_{};
  std::vector<FlowEdge> Edges_;
  std::vector<CostUnit> Potential_, Distance_;
  std::vector<int> Previous_{};
};

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector g(n, std::vector(m, int64_t{}));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Scan(g[i][j]);
    }
  }

  auto id = [m](const int i, const int j) {
    return i * m + j;
  };
  auto ok = [n, m](const int i, const int j) {
    return std::clamp(i, 0, n - 1) == i && std::clamp(j, 0, m - 1) == j;
  };

  constexpr std::array kDi{-1, +0, +0, +1};
  constexpr std::array kDj{+0, -1, +1, +0};

  constexpr int64_t kOffset = 2E12;

  MinCostFlow mcf(n * m + 2);
  const auto s = n * m, t = s + 1;
  int64_t tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      tot += g[i][j];
      if ((i + j) % 2 == 0) {
        mcf.AddEdge(s, id(i, j), 1, 0);
        for (int k = 0; k < 4; ++k) {
          const auto ni = i + kDi[k];
          const auto nj = j + kDj[k];
          if (!ok(ni, nj)) {
            continue;
          }
          mcf.AddEdge(id(i, j), id(ni, nj), 1, g[i][j] + g[ni][nj] + kOffset);
        }
      } else {
        mcf.AddEdge(id(i, j), t, 1, 0);
      }
    }
  }
  const auto [res] = mcf.Slope(s, t);
  auto ret = tot;
  for (const auto [f, c] : res) {
    ret = std::max(ret, tot - (c - f * kOffset));
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Solve();
}

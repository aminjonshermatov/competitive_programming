//
// Created by Aminjon Shermatov on 06.03.2025.
//

#include <bits/stdc++.h>

template <typename DSU>
concept DSUConcept = requires(DSU dsu) {
  typename DSU::Vertex;

  { dsu.Leader(std::declval<typename DSU::Vertex>()) } -> std::same_as<std::size_t>;
  { dsu.Merge(std::declval<typename DSU::Vertex>(), std::declval<typename DSU::Vertex>()) } -> std::same_as<bool>;
  { dsu.IsSame(std::declval<typename DSU::Vertex>(), std::declval<typename DSU::Vertex>()) } -> std::same_as<bool>;
  { dsu.Rank(std::declval<typename DSU::Vertex>()) } -> std::same_as<uint32_t>;
  { dsu.Components() } -> std::same_as<std::size_t>;
};

template <typename DS>
concept RollbackConcept = requires(DS ds) {
  { ds.GetState() } -> std::same_as<int32_t>;
  { ds.Rollback(std::declval<std::size_t>()) } -> std::same_as<void>;
};

template <typename DSUWithRollback>
  requires DSUConcept<DSUWithRollback> && RollbackConcept<DSUWithRollback>
class OfflineDynamicConnectivity final {
 public:
  using Vertex = typename DSUWithRollback::Vertex;
  using Edge = typename std::pair<Vertex, Vertex>;

 public:
  OfflineDynamicConnectivity(const std::size_t nVertices, const std::size_t nQueries)
    : NumberOfVertices_(nVertices)
    , NumberOfQueries_(nQueries)
    , N_{1U << (std::bit_width(2 * NumberOfQueries_ - 1) - 1)}
    , ToAdd_(NumberOfQueries_)
    , ToDelete_(NumberOfQueries_)
    , Tree_(2 * N_ - 1)
    , DSUWithRollback_(nVertices)
  {
  }

  auto AddEdge(const Vertex u, const Vertex v, const std::size_t when) {
    assert(std::clamp(u, {0}, NumberOfVertices_ - 1) == u);
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    assert(std::clamp(when, {0}, NumberOfQueries_ - 1) == when);
    ToAdd_[when].emplace_back(u, v);
  }
  auto RemoveEdge(const Vertex u, const Vertex v, const std::size_t when) {
    assert(std::clamp(u, {0}, NumberOfVertices_ - 1) == u);
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    assert(std::clamp(when, {0}, NumberOfQueries_ - 1) == when);
    ToDelete_[when].emplace_back(u, v);
  }

  auto Prepare() {
    std::map<Edge, std::size_t> edgeCounters, firstAppearance;
    for (std::size_t currentTime{0}; currentTime < NumberOfQueries_; ++currentTime) {
      for (const auto& edge : ToAdd_[currentTime]) {
        if (++edgeCounters[edge] == 1) {
          firstAppearance[edge] = currentTime;
        }
      }
      for (const auto& edge : ToDelete_[currentTime]) {
        if (--edgeCounters[edge] == 0) {
          AddEdgeToSegment(firstAppearance[edge], currentTime, edge, 0, 0, N_);
        }
      }
    }
    for (const auto& [edge, count] : edgeCounters) {
      if (count != 0) {
        AddEdgeToSegment(firstAppearance[edge], NumberOfQueries_, edge, 0, 0, N_);
      }
    }
    IsPrepared_ = true;
  }

  template <typename Add, typename Remove, typename Query>
    requires requires(const Add& add, const Remove& remove, const Query& query) {
      { add(std::declval<Edge>()) } -> std::same_as<void>;
      { remove(std::declval<Edge>()) } -> std::same_as<void>;
      { query(std::declval<std::size_t>()) } -> std::same_as<void>;
    }
  auto Run(const Add& add, const Remove& remove, const Query& query) {
    assert(IsPrepared_);
    Dfs(add, remove, query, 0, 0, N_);
  }

 private:
  auto AddEdgeToSegment(
    const std::size_t ql, const std::size_t qr, const Edge& edge,
    const std::size_t x, const std::size_t lx, const std::size_t rx
  ) -> void {
    if (ql >= rx || qr <= lx) {
      return;
    }
    if (ql <= lx && rx <= qr) {
      Tree_[x].emplace_back(edge);
      return;
    }
    const auto mid = std::midpoint(lx, rx);
    AddEdgeToSegment(ql, qr, edge, 2 * x + 1, lx, mid);
    AddEdgeToSegment(ql, qr, edge, 2 * x + 2, mid, rx);
  }

  template <typename Add, typename Remove, typename Query>
  auto Dfs(
    const Add& add, const Remove& remove, const Query& query,
    const std::size_t x, const std::size_t lx, const std::size_t rx
  ) -> void {
    if (lx >= NumberOfQueries_) {
      return;
    }
    const auto state = DSUWithRollback_.GetState();
    std::vector<const Edge*> edgesBuffer;
    edgesBuffer.reserve(Tree_[x].size());
    for (const Edge& edge : Tree_[x]) {
      if (!DSUWithRollback_.IsSame(edge.first, edge.second)) {
        DSUWithRollback_.Merge(edge.first, edge.second);
        add(edge);
        edgesBuffer.emplace_back(&edge);
      }
    }
    if (rx - lx == 1) {
      query(lx);
    } else {
      const auto mid = std::midpoint(lx, rx);
      Dfs(add, remove, query, 2 * x + 1, lx, mid);
      Dfs(add, remove, query, 2 * x + 2, mid, rx);
    }
    for (const auto* edge : edgesBuffer) {
      remove(*edge);
    }
    DSUWithRollback_.Rollback(state);
  }

 private:
  bool IsPrepared_{false};
  std::size_t NumberOfVertices_{0}, NumberOfQueries_{0}, N_{0};
  std::vector<std::vector<Edge>> ToAdd_, ToDelete_, Tree_;
  DSUWithRollback DSUWithRollback_;
};

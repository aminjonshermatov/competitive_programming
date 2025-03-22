//
// Created by aminjon on 12/1/22.
//
#include <bits/stdc++.h>

class DSU final {
 public:
  using Vertex = std::size_t;

 public:
  explicit DSU(const std::size_t nVertices)
    : NumberOfVertices_(nVertices)
    , Components_(nVertices)
    , Parents_(nVertices)
    , Ranks_(nVertices, 1U)
  {
    std::iota(Parents_.begin(), Parents_.end(), Vertex{0});
  }

  [[nodiscard]] auto Leader(Vertex v) -> Vertex {
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    if (Parents_[v] != v) {
      Parents_[v] = Leader(Parents_[v]);
    }
    return Parents_[v];
  }

  auto Merge(Vertex u, Vertex v) -> bool {
    assert(std::clamp(u, {0}, NumberOfVertices_ - 1) == u);
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    auto pu = Leader(u);
    auto pv = Leader(v);
    if (pu == pv) {
      return false;
    }
    if (Ranks_[pu] < Ranks_[pv]) {
      std::swap(pu, pv);
    }
    Parents_[pv] = pu;
    Ranks_[pu] += Ranks_[pv];
    --Components_;
    return true;
  }

  [[nodiscard]] auto IsSame(const Vertex u, const Vertex v) noexcept -> bool {
    assert(std::clamp(u, {0}, NumberOfVertices_ - 1) == u);
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    return Leader(u) == Leader(v);
  }

  auto Rank(const Vertex v) {
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    return Ranks_[Leader(v)];
  }

  auto Components() const {
    return Components_;
  }

 private:
  std::size_t NumberOfVertices_{0}, Components_{0};
  std::vector<Vertex> Parents_;
  std::vector<uint32_t> Ranks_;
};

template <typename DSU>
concept DSUConcept = requires(DSU dsu) {
  typename DSU::Vertex;

  { dsu.Leader(std::declval<typename DSU::Vertex>()) } -> std::same_as<std::size_t>;
  { dsu.Merge(std::declval<typename DSU::Vertex>(), std::declval<typename DSU::Vertex>()) } -> std::same_as<bool>;
  { dsu.IsSame(std::declval<typename DSU::Vertex>(), std::declval<typename DSU::Vertex>()) } -> std::same_as<bool>;
  { dsu.Rank(std::declval<typename DSU::Vertex>()) } -> std::same_as<uint32_t>;
  { dsu.Components() } -> std::same_as<std::size_t>;
};

static_assert(DSUConcept<DSU>);

class DSUWithRollbacks final {
 public:
  using Vertex = std::size_t;

 public:
  explicit DSUWithRollbacks(const std::size_t nVertices)
    : NumberOfVertices_(nVertices)
    , Components_(nVertices)
    , Infos_(nVertices, -1)
  { }

  [[nodiscard]] auto Leader(Vertex v) -> Vertex {
    if (Infos_[v] < 0) {
      return v;
    }
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    return Leader(Infos_[v]);
  }

  auto Merge(Vertex u, Vertex v) -> bool {
    assert(std::clamp(u, {0}, NumberOfVertices_ - 1) == u);
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    auto pu = Leader(u);
    auto pv = Leader(v);
    if (pu == pv) {
      return false;
    }
    History_.emplace(&Infos_[pu], Infos_[pu]);
    History_.emplace(&Infos_[pv], Infos_[pv]);
    assert(Infos_[pu] < 0);
    assert(Infos_[pv] < 0);
    if (-Infos_[pu] < -Infos_[pv]) {
      std::swap(pu, pv);
    }
    Infos_[pu] += Infos_[pv];
    Infos_[pv] = pu;
    --Components_;
    return true;
  }

  [[nodiscard]] auto IsSame(const Vertex u, const Vertex v) noexcept -> bool {
    assert(std::clamp(u, {0}, NumberOfVertices_ - 1) == u);
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    return Leader(u) == Leader(v);
  }

  [[nodiscard]] auto Rank(const Vertex v) -> uint32_t {
    assert(std::clamp(v, {0}, NumberOfVertices_ - 1) == v);
    return static_cast<uint32_t>(-Infos_[Leader(v)]);
  }

  auto Components() const {
    return Components_;
  }

  auto GetState() const {
    return static_cast<int32_t>(History_.size());
  }

  auto Rollback(const int32_t state) {
    for (assert(state <= GetState()); state < GetState(); Undo()) { }
  }

 private:
  auto Undo() -> void {
    *History_.top().first = History_.top().second;
    History_.pop();
  }

 private:
  std::size_t NumberOfVertices_{0}, Components_{0};
  std::vector<int64_t> Infos_;
  std::stack<std::pair<decltype(Infos_)::pointer, decltype(Infos_)::value_type>> History_;
};

template <typename DS>
concept RollbackConcept = requires(DS ds) {
  { ds.GetState() } -> std::same_as<int32_t>;
  { ds.Rollback(std::declval<std::size_t>()) } -> std::same_as<void>;
};

static_assert(DSUConcept<DSUWithRollbacks> && RollbackConcept<DSUWithRollbacks>);

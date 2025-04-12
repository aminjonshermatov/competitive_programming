#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector lo(n, std::vector<int>{}), hi(n, std::vector<int>{});
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    assert(u < v);
    lo[v].emplace_back(u);
    hi[u].emplace_back(v);
  }

  DSU dsu(n);
  std::vector<int> ret(n);
  std::vector removed(n, false), isGood(n, true);
  for (int i = 0; i < n; ++i) {
    if (removed[i]) {
      --ret[i];
    } else {
      removed[i] = true;
    }
    for (auto u : lo[i]) {
      dsu.Merge(i, u);
    }
    for (auto u : hi[i]) {
      if (!removed[u]) {
        ++ret[i];
        removed[u] = true;
      }
    }
    if (dsu.Rank(0) != i + 1) {
      isGood[i] = false;
    }
  }
  dbg(ret);
  std::partial_sum(ret.begin(), ret.end(), ret.begin());
  for (int i = 0; i < n; ++i) {
    Print(isGood[i] ? ret[i] : -1);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

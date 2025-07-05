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

void Solve() {
  int n, m, k;
  Scan(n, m, k);
  std::map<std::pair<int, int>, int> os;
  for (int i = 0; i < k; ++i) {
    int x, y;
    Scan(x, y);
    os.emplace(std::pair{x, y}, i);
  }

  DSU dsu(k + 2);
  for (const auto& [o, i] : os) {
    if ((o.first == 1 && o.second > 1) || (o.second == m && o.first < n)) {
      dsu.Merge(k, i);
    }
    if ((o.second == 1 && o.first > 1) || (o.first == n && o.second < m)) {
      dsu.Merge(k + 1, i);
    }
    for (auto di = -1; di <= 1; ++di) {
      for (auto dj = -1; dj <= 1; ++dj) {
        auto no = o;
        no.first += di;
        no.second += dj;
        if (std::clamp(no.first, 1, n) == no.first && std::clamp(no.second, 1, m) == no.second && os.contains(no)) {
          dsu.Merge(i, os[no]);
        }
      }
    }
  }
  Println(dsu.IsSame(k, k + 1) ? "No" : "Yes");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

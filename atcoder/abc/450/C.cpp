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
  int n, m;
  Scan(n, m);
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  auto id = [m](const int i, const int j) {
    return i * m + j;
  };

  DSU dsu(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (j + 1 < m && g[i][j] == g[i][j + 1]) {
        dsu.Merge(id(i, j), id(i, j + 1));
      }
      if (i + 1 < n && g[i][j] == g[i + 1][j]) {
        dsu.Merge(id(i, j), id(i + 1, j));
      }
    }
  }
  for (int i = 0; i < n * m; ++i) {
    auto x = dsu.Leader(i);
  }
  std::set<int> qwe;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '.') {
        qwe.emplace(dsu.Leader(id(i, j)));
      }
    }
  }
  for (auto i : {0, n - 1}) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '.') {
        const auto l = dsu.Leader(id(i, j));
        if (qwe.contains(l)) {
          qwe.erase(l);
        }
      }
    }
  }
  for (auto j : {0, m - 1}) {
    for (int i = 0; i < n; ++i) {
      if (g[i][j] == '.') {
        const auto l = dsu.Leader(id(i, j));
        if (qwe.contains(l)) {
          qwe.erase(l);
        }
      }
    }
  }
  Println(qwe.size());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

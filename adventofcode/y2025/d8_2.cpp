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

struct Point {
  int64_t X = 0, Y = 0, Z = 0;

  friend std::ostream& operator<<(std::ostream& out, const Point& pt) {
    return out << std::format("{{{},{},{}}}", pt.X, pt.Y, pt.Z);
  }
};

void Solve() {
  constexpr int kN = 1000;
  std::array<Point, kN> pts;
  for (char  _; auto& [x, y, z] : pts) {
    Scan(x, _, y, _, z);
  }

  auto sqr = [](const auto x) {
    return x * x;
  };

  std::array<std::tuple<int64_t, int, int>, kN * (kN - 1) / 2> es;
  for (int i = 0, ptr = 0; i < kN; ++i) {
    for (int j = i + 1; j < kN; ++j) {
      es[ptr++] = std::tuple(
        sqr(pts[i].X - pts[j].X) + sqr(pts[i].Y - pts[j].Y) + sqr(pts[i].Z - pts[j].Z),
        i, j
      );
    }
  }

  std::ranges::sort(es);
  DSU dsu(kN);
  std::optional<std::pair<int64_t, int64_t>> is;
  for (const auto [_, i, j] : es) {
    if (dsu.Merge(i,j)) {
      is.emplace(pts[i].X, pts[j].X);
    }
  }
  dbg(is->first,is->second);
  Println(is->first * is->second);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

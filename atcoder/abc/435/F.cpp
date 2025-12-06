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
    , Lft(nVertices)
    , Rgt(nVertices)
    , Ranks_(nVertices, 1U)
  {
    std::iota(Parents_.begin(), Parents_.end(), Vertex{0});
    std::iota(Lft.begin(), Lft.end(), 0);
    std::iota(Rgt.begin(), Rgt.end(), 0);
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
    Lft[pu] = std::min(Lft[pu], Lft[pv]);
    Rgt[pu] = std::max(Rgt[pu], Rgt[pv]);
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

 public:
  std::vector<int> Lft, Rgt;

 private:
  std::size_t NumberOfVertices_{0}, Components_{0};
  std::vector<Vertex> Parents_;
  std::vector<uint32_t> Ranks_;
};

template <typename Info>
class BottomUpSegmentTree {
 public:
  BottomUpSegmentTree() = default;

  explicit BottomUpSegmentTree(std::size_t n) {
    Init(std::vector(n, Info{}));
  }
  BottomUpSegmentTree(std::size_t n, Info&& info) {
    Init(std::vector(n, std::forward<Info>(info)));
  }
  template <typename T>
  explicit BottomUpSegmentTree(const std::vector<T>& init) {
    Init(init);
  }

  template <typename T>
  void Init(const std::vector<T>& init) {
    assert(!init.empty());
    N_ = 1u << (std::bit_width(2 * init.size() - 1) - 1);
    Infos_.assign(2 * N_, Info{});
    for (std::size_t i{0}; i < init.size(); ++i) {
      Infos_[i + N_] = Info{init[i]};
    }
    for (std::size_t i = N_ - 1; i >= 1u; --i) {
      Infos_[i] = Infos_[i << 1] + Infos_[i << 1 | 1];
    }
  }

  void Modify(std::size_t pos, Info&& val) {
    Infos_[pos += N_] = val;
    for (pos >>= 1; pos >= 1; pos >>= 1) {
      Infos_[pos] = Infos_[pos << 1] + Infos_[pos << 1 | 1];
    }
  }

  Info Query(std::size_t l, std::size_t r) {
    auto retL = Info{}, retR = Info{};
    for (l += N_, r += N_; l < r; l >>= 1, r >>= 1) {
      if (l % 2 == 1u) {
        retL = retL + Infos_[l++];
      }
      if (r % 2 == 1u) {
        retR = Infos_[--r] + retR;
      }
    }
    return retL + retR;
  }

  Info Query(std::size_t pos) {
    return Query(pos, pos + 1);
  }

 private:
  std::size_t N_{0};
  std::vector<Info> Infos_;
};

constexpr auto kInf = std::numeric_limits<int64_t>::max() / 2;
class Info {
 public:
  int64_t Val = -kInf, Id = -1;

  auto operator<=>(const Info&) const = default;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return lhs > rhs ? lhs : rhs;
}

void Solve() {
  int n;
  Scan(n);
  std::vector<int> ps(n);
  for (int i = 0; i < n; ++i) {
    Scan(ps[i]);
  }

  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return ps[i] < ps[j];
  });

  std::vector dp(n, -kInf);
  DSU dsu(n);
  BottomUpSegmentTree<Info> st(n);
  for (int i = 0; i < n; ++i) {
    st.Modify(i, {ps[i], i});
  }
  for (const auto id : ord) {
    if (id > 0 && ps[id] > ps[id - 1]) {
      dsu.Merge(id, id - 1);
    }
    if (id + 1 < n && ps[id] > ps[id + 1]) {
      dsu.Merge(id, id + 1);
    }
    const auto p = dsu.Leader(id);
    const auto l = dsu.Lft[p];
    const auto r = dsu.Rgt[p];
    dp[id] = 0;
    if (const auto lhs = st.Query(l, id); lhs.Id != -1) {
      dp[id] = std::max(dp[id], dp[lhs.Id] + id - lhs.Id);
    }
    if (const auto rhs = st.Query(id + 1, r + 1); rhs.Id != -1) {
      dp[id] = std::max(dp[id], dp[rhs.Id] + rhs.Id - id);
    }
  }
  dbg(dp);
  Println(dp[std::ranges::find(ps, n) - ps.begin()]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

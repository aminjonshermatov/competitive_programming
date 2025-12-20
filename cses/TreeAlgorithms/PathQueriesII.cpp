#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

class HeavyLightDecomposition final {
 public:
  template<typename G>
  explicit HeavyLightDecomposition(const G &g) : N_(static_cast<int>(g.size())) {
    Parent_.assign(N_, -1);
    Root_.assign(N_, -1);
    TreePos_.assign(N_, -1);
    Heavy_.assign(N_, -1);
    Depth_.resize(N_);
    Depth_[0] = 0;
    Dfs(g, 0);

    for (auto u = 0, currentPos = 0; u < N_; ++u) {
      if (Parent_[u] == -1 || Heavy_[Parent_[u]] != u) {
        for (auto v = u; v != -1; v = Heavy_[v]) {
          Root_[v] = u;
          TreePos_[v] = currentPos++;
        }
      }
    }
  }

  template <typename F>
  auto Modify(const int v, F&& f) {
    Modify(v, v, std::move(f));
  }

  template <typename F>
  auto Modify(const int u, const int v, F&& f) { // [u, v]
    ProcessPath(u, v, [f = std::move(f)](const int l, const int r) {
      f(l, r); // [l, r)
    });
  }

  template <typename F>
  auto Query(const int u, const int v, F&& f) { // [u, v]
    ProcessPath(u, v, std::move(f));
  }

  auto Pos(const int v) const {
    assert(std::clamp(v, 0, N_ - 1) == v);
    return TreePos_[v];
  }

 private:
  template<typename BinaryOP>
  void ProcessPath(int u, int v, BinaryOP&& op) {
    for (; Root_[u] != Root_[v]; v = Parent_[Root_[v]]) {
      if (Depth_[Root_[u]] > Depth_[Root_[v]]) {
        std::swap(u, v); // u closer to lca rather than v
      }
      op(TreePos_[Root_[v]], TreePos_[v] + 1);
    }
    if (Depth_[u] > Depth_[v]) {
      std::swap(u, v);
    }
    op(TreePos_[u], TreePos_[v] + 1);
  }

  template<typename G>
  auto Dfs(const G &g, const int v) -> int {
    auto size = 1, maxSubtree = 0;
    for (auto u : g[v]) {
      if (u == Parent_[v]) {
        continue;
      }
      Parent_[u] = v;
      Depth_[u] = Depth_[v] + 1;
      auto subtree = Dfs(g, u);
      if (subtree > maxSubtree) {
        Heavy_[v] = u;
        maxSubtree = subtree;
      }
      size += subtree;
    }
    return size;
  }

 private:
  const int N_ = 0;
  std::vector<int> Parent_, Root_, Depth_, TreePos_, Heavy_;
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

constexpr auto kInf = std::numeric_limits<int>::max() / 2;
class Info {
 public:
  int Val = -kInf;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {std::max(lhs.Val, rhs.Val)};
}

void Solve() {
  int n, q;
  Scan(n, q);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i + 1 < n; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  HeavyLightDecomposition hld(g);
  std::vector<Info> init(n);
  for (int i = 0; i < n; ++i) {
    init[hld.Pos(i)] = Info{as[i]};
  }
  BottomUpSegmentTree<Info> st(init);

  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int v, x;
      Scan(v, x);
      --v;

      hld.Modify(v, [&st, x](const int l, const int r) {
        assert(r - l == 1);
        st.Modify(l, {x});
      });
    } else if (cmd == '2') {
      int u, v;
      Scan(u, v);
      --u, --v;

      auto ret = -kInf;
      hld.Query(u, v, [&ret, &st](const int l, const int r) {
        ret = std::max(ret, st.Query(l, r).Val);
      });
      Print(ret);
    } else {
      assert(false);
    }
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
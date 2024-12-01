#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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

constexpr auto kInf = std::numeric_limits<int>::max() / 3;
class Info {
 public:
  int Val = kInf;
};
Info operator+(const Info& lhs, const Info& rhs) {
  return {std::min(lhs.Val, rhs.Val)};
}

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector<int> as(n), bs(m);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  for (int i = 0; i < m; ++i) {
    Scan(bs[i]);
  }

  auto xs = as;
  xs.insert(xs.end(), bs.begin(), bs.end());
  std::ranges::sort(xs);
  xs.erase(std::ranges::unique(xs).begin(), xs.end());
  const auto k = std::ssize(xs);
  for (int i = 0; i < n; ++i) {
    as[i] = static_cast<int>(std::distance(xs.begin(), std::ranges::lower_bound(xs, as[i])));
  }
  for (int i = 0; i < m; ++i) {
    bs[i] = static_cast<int>(std::distance(xs.begin(), std::ranges::lower_bound(xs, bs[i])));
  }

  std::vector que(k, kInf);
  for (int i = 0; i < n; ++i) {
    que[as[i]] = std::min(que[as[i]], i);
  }
  BottomUpSegmentTree<Info> st(que);
  std::vector<int> ret(m, -1);
  for (int i = 0; i < m; ++i) {
    ret[i] = st.Query(0, bs[i] + 1).Val;
  }
  for (int i = 0; i < m; ++i) {
    Print(ret[i] == kInf ? -1 : (ret[i] + 1));
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

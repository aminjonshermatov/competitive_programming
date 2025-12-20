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

constexpr int64_t kInf = std::numeric_limits<int64_t>::max() / 3;
class Info {
 public:
  Info() = default;
  Info(const int64_t d, const int64_t s) : MinD(d), MaxD(d), MinS(s), MaxS(s) { }
  int64_t MinD = kInf, MaxD = -kInf;
  int64_t MinS = kInf, MaxS = -kInf;
};
Info operator+(const Info& lhs, const Info& rhs) {
  Info ret;
  ret.MinD = std::min(lhs.MinD, rhs.MinD);
  ret.MaxD = std::max(lhs.MaxD, rhs.MaxD);
  ret.MinS = std::min(lhs.MinS, rhs.MinS);
  ret.MaxS = std::max(lhs.MaxS, rhs.MaxS);
  return ret;
}

void Solve() {
  int n, q;
  Scan(n, q);
  std::vector<Info> init(n);
  for (int i = 0; i < n; ++i) {
    int64_t x, y;
    Scan(x, y);
    init[i] = Info(x - y, x + y);
  }
  BottomUpSegmentTree<Info> st(init);
  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int i, x, y;
      Scan(i, x, y);

      st.Modify(i - 1, Info(x - y, x + y));
    } else {
      int l, r;
      int64_t x, y;
      Scan(l, r, x, y);
      --l, --r;

      const auto d = x - y;
      const auto s = x + y;

      auto info = st.Query(l, r + 1);
      auto ret = -kInf;
      ret = std::max(ret, info.MaxD - d);
      ret = std::max(ret, d - info.MinD);
      ret = std::max(ret, info.MaxS - s);
      ret = std::max(ret, s - info.MinS);
      Println(ret);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

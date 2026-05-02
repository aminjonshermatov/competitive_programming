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

constexpr auto kInf = std::numeric_limits<int64_t>::max() / 3;

class Info {
 public:
  Info() = default;
  explicit Info(const int64_t x) {
    Vals[0 * 2 + 0] = 0;
    Vals[1 * 2 + 1] = x;
  }
  std::array<int64_t, 4> Vals{kInf, kInf, kInf, kInf};

  auto operator<=>(const Info&) const = default;
};
Info operator+(const Info& lhs, const Info& rhs) {
  if (lhs == Info{}) {
    return rhs;
  }
  if (rhs == Info{}) {
    return lhs;
  }
  Info ret{};
  for (int al = 0; al < 2; ++al) {
    for (int ar = 0; ar < 2; ++ar) {
      for (int bl = 0; bl < 2; ++bl) {
        for (int br = 0; br < 2; ++br) {
          if (ar == 0 && bl == 0) {
            continue;
          }
          ret.Vals[al * 2 + br] = std::min(ret.Vals[al * 2 + br], lhs.Vals[al * 2 + ar] + rhs.Vals[bl * 2 + br]);
        }
      }
    }
  }
  return ret;
}

void Solve() {
  int n, k;
  Scan(n, k);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  BottomUpSegmentTree<Info> st(as);
  auto ret = kInf;
  for (int i = 0; i + k <= n; ++i) {
    ret = std::min(ret, st.Query(i, i + k).Vals[1 * 2 + 1]);
    if (i + k + 1 <= n) {
      ret = std::min(ret, st.Query(i, i + k + 1).Vals[1 * 2 + 1]);
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}

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

class Info {
 public:
  int Val = 0;
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
  auto bs = as;
  std::ranges::sort(bs);
  bs.erase(std::ranges::unique(bs).begin(), bs.end());
  for (int i = 0; i < n; ++i) {
    as[i] = static_cast<int>(std::distance(bs.begin(), std::ranges::lower_bound(bs, as[i])));
  }
  const auto m = int(bs.size());

  std::vector<std::pair<int, int>> qs(q);
  for (auto& [r, x] : qs) {
    Scan(r, x);
    --r;
  }
  std::vector<int> ord(q);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return qs[i].first < qs[j].first;
  });
  std::vector<int> ret(q);
  std::size_t ptr{0};

  BottomUpSegmentTree<Info> st(m);
  auto at = [&st](int pos) {
    return st.Query(pos).Val;
  };
  dbg(ord);
  for (int i = 0; i < n; ++i) {
    st.Modify(as[i], {std::max(at(as[i]), st.Query(0, as[i]).Val + 1)});
    while (ptr < q && qs[ord[ptr]].first <= i) {
      ret[ord[ptr]] = st.Query(0, std::distance(bs.begin(), std::ranges::upper_bound(bs, qs[ord[ptr]].second))).Val;
      ++ptr;
    }
  }
  for (int i = 0; i < q; ++i) {
    Print(ret[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

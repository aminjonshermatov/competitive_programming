#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

static constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
static constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
static constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

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

class Info final {
public:
  Info() = default;
  Info(const int x) {
    Xs = {{x, 1}};
  }
  std::vector<std::pair<int, int>> Xs;
};
static Info operator+(Info lhs, Info rhs) {
  if (lhs.Xs.empty()) {
    return rhs;
  }
  if (rhs.Xs.empty()) {
    return lhs;
  }
  if (lhs.Xs.front().first > rhs.Xs.front().first) {
    std::swap(lhs, rhs);
  }
  Info loc{};
  auto ptr = 0;
  for (const auto [x, y] : lhs.Xs) {
    while (ptr < rhs.Xs.size() && rhs.Xs[ptr].first < x) {
      if (loc.Xs.size() == 3) {
        break;
      }
      loc.Xs.emplace_back(rhs.Xs[ptr++]);
    }
    if (loc.Xs.size() == 3) {
      break;
    }
    loc.Xs.emplace_back(x, y);
    if (ptr < rhs.Xs.size() && rhs.Xs[ptr].first == x) {
      loc.Xs.back().second += rhs.Xs[ptr++].second;
    }
  }
  while (ptr < rhs.Xs.size() && loc.Xs.size() < 3) {
    loc.Xs.emplace_back(rhs.Xs[ptr++]);
  }
  return loc;
}

static void Solve() {
  int n, q;
  Scan(n, q);
  std::vector as(n, 0);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  BottomUpSegmentTree<Info> st(as);
  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int i, x;
      Scan(i, x);
      st.Modify(i - 1, Info(x));
    } else {
      int l, r;
      Scan(l, r);
      const auto [xs] = st.Query(l - 1, r);
      assert(!xs.empty());
      if (xs.size() > 2) {
        Println("No");
        continue;
      }
      if (xs.size() == 1 || xs[0].first == -1) {
        Println("Yes");
        continue;
      }
      Println("No");
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

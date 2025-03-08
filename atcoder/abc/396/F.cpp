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
class FenwickTree {
 public:
  FenwickTree() = default;
  explicit FenwickTree(const int n) {
    Init(std::vector(n, Info{}));
  }
  FenwickTree(const int n, const Info& info) {
    Init(std::vector(n, info));
  }
  template<typename U>
  explicit FenwickTree(const std::vector<U>& as) {
    std::vector<Info> init(as.size());
    std::ranges::generate(init, [id = std::size_t{0}, &as]() mutable {
      return Info{as[id++]};
    });
    Init(init);
  }

  auto Init(const std::vector<Info>& init) {
    N_ = static_cast<int>(init.size());
    Bit_.assign(N_, Info{});
    for (int i = 0; i < N_; ++i) {
      Modify(i, init[i]);
    }
  }

  auto Modify(const int idx, const Info& val) {
    for (auto id = idx; id < N_; id = id | (id + 1)) {
      Bit_[id] = Bit_[id] + val;
    }
  }

  auto Query(const int idx) const -> Info {
    return Query(idx, idx + 1);
  }

  // [l, r)
  auto Query(const int l, const int r) const -> Info {
    return QueryImpl(r - 1) - QueryImpl(l - 1);
  }

 private:
  auto QueryImpl(const int idx) const -> Info {
    auto ret = Info{};
    for (auto id = idx; id >= 0; id = (id & (id + 1)) - 1) {
      ret = ret + Bit_[id];
    }
    return ret;
  }

 private:
  int N_{0};
  std::vector<Info> Bit_;
};

void Solve() {
  int n, m;
  Scan(n, m);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  FenwickTree<int64_t> lhs(m), rhs(m);
  for (int i = 0; i < n; ++i) {
    rhs.Modify(as[i], +1);
  }
  // i < j
  // as[i] < as[j]:
  //  [m-as[j], m-as[i])
  // as[i] > as[j]:
  //  [0, m-as[i]) | [m-as[j], m)
  std::vector<int64_t> ret(m + 1, 0);
  for (int i = 0; i < n; ++i) {
    rhs.Modify(as[i], -1);
    {
      const auto gt = rhs.Query(as[i] + 1, m);
      ret[m - as[i]] -= gt;
      const auto lt = lhs.Query(0, as[i]);
      ret[m - as[i]] += lt;
    }
    {
      const auto lt = rhs.Query(0, as[i]);
      ret[0] += lt;
      ret[m - as[i]] -= lt;
      const auto gt = lhs.Query(as[i] + 1, m);
      ret[m - as[i]] += gt;
      ret[m] -= gt;
    }
    lhs.Modify(as[i], +1);
  }
  for (int i = 0; i < m; ++i) {
    if (i > 0) {
      ret[i] += ret[i - 1];
    }
    Print(ret[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

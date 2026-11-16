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

static void Solve() {
  int n;
  int64_t l, r;
  Scan(n, l, r);
  std::vector as(n, 0LL);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  std::vector pf(n, 0LL);
  pf[0] = as[0];
  for (int i = 1; i < n; ++i) {
    pf[i] = pf[i - 1] + as[i];
  }
  auto all = pf;
  std::ranges::sort(all);
  all.erase(std::ranges::unique(all).begin(), all.end());
  FenwickTree<int> ft(all.size());
  for (int i = 0; i < n; ++i) {
    ft.Modify(std::ranges::lower_bound(all, pf[i]) - all.begin(), +1);
  }
  auto tot = 0LL;
  for (int i = 0; i < n; ++i) {
    // pf[j] - pf[i-1] >= l && pf[j] - pf[i-1] <= r
    const auto x = i > 0 ? pf[i - 1] : 0;
    tot += ft.Query(
      std::ranges::lower_bound(all, x + l) - all.begin(),
      std::ranges::upper_bound(all, x + r) - all.begin()
    );
    ft.Modify(std::ranges::lower_bound(all, pf[i]) - all.begin(), -1);
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

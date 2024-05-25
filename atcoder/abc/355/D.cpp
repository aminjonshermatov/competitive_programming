#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <typename T> struct FenwickTreePointUpdateRangeQuery {
  int n = 0;
  std::vector<T> bit;

  FenwickTreePointUpdateRangeQuery() = default;
  explicit FenwickTreePointUpdateRangeQuery(int n_) : n(n_), bit(n_, T(0))  { }
  template<typename U> explicit FenwickTreePointUpdateRangeQuery(const std::vector<U> &A) : n(A.size()), bit(A.size(), T(0)) {
    for (auto idx = 0u; idx < n; ++idx) {
      modify(idx, A[idx]);
    }
  }

  void init(int n_) {
    n = n_;
    bit.assign(n, T(0));
  }

  auto modify(int idx, T val) -> void {
    for (; idx < n; idx = idx | (idx + 1)) {
      bit[idx] += val;
    }
  }

  [[nodiscard]] auto query(int idx) const -> T {
    T ret = T(0);
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
      ret += bit[idx];
    }
    return ret;
  }

  [[nodiscard]] auto query(int l, int r) const -> T { // [l, r)
    return query(r - 1) - query(l - 1);
  }
};

void solve() {
  int n;
  scan(n);
  std::vector<std::pair<int, int>> xs(n);
  std::vector<int> all;
  for (auto&& [l, r] : xs) {
    scan(l, r);
    all.emplace_back(l);
    all.emplace_back(r);
  }
  std::ranges::sort(all);
  all.erase(std::ranges::unique(all).begin(), all.end());
  for (auto&& [l, r] : xs) {
    l = int(std::ranges::lower_bound(all, l) - all.begin());
    r = int(std::ranges::lower_bound(all, r) - all.begin());
  }

  const auto m = int(all.size());
  FenwickTreePointUpdateRangeQuery<int> ft(m);
  std::ranges::sort(xs);
  int64_t tot{};
  for (auto& [l, r] : xs) {
    tot += ft.query(l, m);
    ft.modify(r, +1);
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::vector<i64> as(n);
  for (auto&& a : as) {
    scan(a);
  }

  std::ranges::sort(as);
  std::vector<i64> pf(n);
  for (int i = 0; i < n; ++i) {
    pf[i] = (i > 0 ? pf[i - 1] : 0) + as[i];
  }
  auto get = [&](int l, int r) -> i64 {
    if (l > r) {
      return 0;
    }
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };

  i64 tot = 0;
  constexpr i64 x = 1e8;
  for (int i = 0; i < n; ++i) {
    const auto pos = int(std::ranges::lower_bound(as.begin() + i + 1, as.end(), x - as[i]) - as.begin());
    assert(pos == n || as[i] + as[pos] >= x);
    tot += get(i + 1, pos - 1) + as[i] * std::max(0, pos - 1 - i - 1 + 1) + get(pos, n - 1) + (as[i] - x) * (n - pos);
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
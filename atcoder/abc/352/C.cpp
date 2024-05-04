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
  std::vector<i64> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    scan(as[i], bs[i]);
  }
  const auto all = std::accumulate(as.begin(), as.end(), i64{});
  i64 best = 0;
  for (int i = 0; i < n; ++i) {
    best = std::max(best, all - as[i] + bs[i]);
  }
  println(best);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
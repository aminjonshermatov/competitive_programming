#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int64_t n;
  Scan(n);
  auto ret = 0LL;
  for (__int128 a = 2; a <= n; a *= 2) {
    __int128 lo = 1, hi = n / a + 1;
    while (hi - lo > 1) {
      const auto mid = std::midpoint(lo, hi);
      const auto b = 2 * mid - 1;
      (a * b * b <= n ? lo : hi) = mid;
    }
    ret += lo;
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

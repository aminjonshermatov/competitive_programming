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
  int64_t n, k;
  Scan(n, k);

  // n+x, for x=0..
  // n*(mid+1) + mid*(mid+1)/2

  // mid=0 -> n
  // mid=1 -> 2n + 1
  // mid=6 -> 7n + 21

  if (n >= k) {
    Println(0);
    return;
  }

  int64_t lo = 0, hi = 1E18;
  while (hi - lo > 1) {
    const auto mid = std::midpoint(lo, hi);
    (__int128(n) * (mid + 1) + __int128(mid) * (mid + 1) / 2 < k ? lo : hi) = mid;
  }
  Println(hi);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

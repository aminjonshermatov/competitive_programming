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
  int n, k;
  Scan(n, k);
  __int128 x = 1;
  for (int _ = 0; _ < n; ++_) {
    int64_t a;
    Scan(a);
    x *= a;
    auto cnt = 0;
    for (auto tmp = x; tmp > 0; ++cnt, tmp /= 10) { }
    if (cnt > k) {
      x = 1;
    }
  }
  Println(int64_t(x));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

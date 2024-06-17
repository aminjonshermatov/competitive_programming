#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, a;
  scan(n, a);
  int prv = -1;
  for (int i = 0; i < n; ++i) {
    int t;
    scan(t);
    const auto d = (prv == -1 ? 0 : prv) - t;
    int z = t + a;
    if (d > 0) {
      z += d;
    }
    println(z);
    prv = z;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
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

  std::vector buf(n - 1, 0);
  [&](this auto self, const int i, const int rem) -> void {
    if (i + 1 >= n) {
      if (rem % n == 0) {
        for (const auto x : buf) {
          Print(x);
        }
        Println(rem / n);
      }
      return;
    }
    for (int x = 0; (i + 1) * x <= rem; ++x) {
      buf[i] = x;
      self(i + 1, rem - (i + 1) * x);
    }
  }(0, k);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

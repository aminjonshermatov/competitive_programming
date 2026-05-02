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
  std::vector as(3, std::vector(6, 0));
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 6; ++j) {
      Scan(as[i][j]);
    }
  }
  auto tot = 0;
  for (auto a : as[0]) {
    for (auto b : as[1]) {
      for (auto c : as[2]) {
        std::array tmp{a, b, c};
        std::ranges::sort(tmp);
        tot += tmp == std::array{4, 5, 6};
      }
    }
  }
  Println(tot / 6.0 / 6.0 / 6.0);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

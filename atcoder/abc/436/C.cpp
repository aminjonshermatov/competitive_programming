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
  int n, m;
  Scan(n, m);
  std::set<std::pair<int, int>> xs;
  auto tot = 0;
  while (m-- > 0) {
    int r, c;
    Scan(r, c);

    auto f = true;
    for (int dr = 0; dr < 2; ++dr) {
      for (int dc = 0; dc < 2; ++dc) {
        f &= !xs.contains(std::pair(r + dr, c + dc));
      }
    }
    if (f) {
      for (int dr = 0; dr < 2; ++dr) {
        for (int dc = 0; dc < 2; ++dc) {
          xs.emplace(r + dr, c + dc);
        }
      }
      ++tot;
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

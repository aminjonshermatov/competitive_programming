#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

static constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
static constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
static constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

static void Solve() {
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

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
  int n;
  Scan(n);
  std::vector as(n, 0);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  auto tot = 1LL;
  std::map<int, int> qty;
  ++qty[as[0]];
  for (int i = 1; i < n; ++i) {
    if (as[i] != as[i - 1]) {
      tot += i - qty[as[i]];
    }
    ++qty[as[i]];
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

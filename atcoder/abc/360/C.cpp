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
  int n;
  scan(n);
  std::vector<int> as(n);
  for (auto&& a : as) {
    scan(a);
    --a;
  }
  std::vector<std::vector<int>> xs(n);
  for (int i = 0; i < n; ++i) {
    int w;
    scan(w);
    xs[as[i]].emplace_back(w);
  }
  int tot{};
  for (auto&& x : xs) {
    std::ranges::sort(x);
    std::ranges::reverse(x);
    for (auto&& y : x | std::views::drop(1)) {
      tot += y;
    }
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
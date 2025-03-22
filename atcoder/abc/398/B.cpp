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
  std::map<int, int> cnt;
  for (int i = 0; i < 7; ++i) {
    int x;
    Scan(x);
    ++cnt[x];
  }
  std::vector<int> xs;
  for (auto x : cnt | std::ranges::views::values) {
    xs.emplace_back(x);
  }
  std::ranges::sort(xs, std::greater{});
  dbg(xs);
  Println(xs.size() >= 2 && xs[0] >= 3 && xs[1] >= 2 ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

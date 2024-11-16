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
  std::map<char, int> cnt{};
  for (int i = 0; i < 6; ++i) {
    char c;
    Scan(c);
    ++cnt[c];
  }
  std::vector<int> xs;
  for (auto [k, v] : cnt) {
    xs.emplace_back(v);
  }
  Println(xs == std::vector{1, 2, 3} ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

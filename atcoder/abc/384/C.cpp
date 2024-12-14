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
  std::array<int, 5> xs{};
  for (int i = 0; i < 5; ++i) {
    Scan(xs[i]);
  }
  std::vector<std::pair<int, std::string>> all;
  for (uint32_t m = 1; m < (1 << 5); ++m) {
    int cur = 0;
    std::string s;
    for (auto tmp = m; tmp > 0;) {
      auto b = std::bit_width(tmp) - 1;
      cur += xs[b];
      s.push_back('A' + b);
      tmp ^= 1 << b;
    }
    std::ranges::reverse(s);
    all.emplace_back(-cur, s);
  }
  std::ranges::sort(all);
  for (auto& [_, s] : all) {
    Println(s);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

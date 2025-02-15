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
  std::string s;
  Scan(s);

  const auto n = int(s.size());
  auto tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      const auto len = i - j + 1;
      if (i + len <= n) {
        tot += s[j] == 'A' && s[i] == 'B' && s[i + len - 1] == 'C';
      }
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

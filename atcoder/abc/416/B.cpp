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
  for (int i = 0, prv = -1; i < n; ++i) {
    if (s[i] == '#') {
      if (prv + 1 < i) {
        s[prv + 1] = 'o';
      }
      prv = i;
    } else if (i + 1 == n) {
      s[prv + 1] = 'o';
    }
  }
  Println(s);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

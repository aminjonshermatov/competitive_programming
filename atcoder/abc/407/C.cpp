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

  auto ret = n;
  for (int i = n - 1, suf = 0; i >= 0; --i) {
    const auto x = (s[i] - '0' + 10 - suf) % 10;
    ret += x;
    if ((suf += x) >= 10) {
      suf -= 10;
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Solve();
}

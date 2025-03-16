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
  auto loc = 0;
  for (auto cur = 'i'; auto c : s) {
    if (cur != c) {
      ++loc;
    } else {
      cur = 'i' ^ 'o' ^ cur;
    }
  }
  if ((loc + s.size()) % 2 == 1) {
    ++loc;
  }
  Println(loc);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

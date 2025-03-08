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
  int q;
  Scan(q);
  std::vector stk(101, 0);
  while (q-- > 0) {
    char cmd;
    Scan(cmd);
    if (cmd == '1') {
      int x;
      Scan(x);
      stk.emplace_back(x);
    } else {
      Println(stk.back());
      stk.pop_back();
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

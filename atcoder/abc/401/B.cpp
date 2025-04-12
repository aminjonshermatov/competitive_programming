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
  int n;
  Scan(n);

  auto isLogged = false;
  auto ret401 = 0;
  for (int i = 0; i < n; ++i) {
    std::string cmd;
    Scan(cmd);
    if (cmd == "login") {
      isLogged = true;
    } else if (cmd == "logout") {
      isLogged = false;
    } else if (cmd == "public") {
      continue;
    } else if (cmd == "private") {
      ret401 += !isLogged;
    }
  }
  Println(ret401);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

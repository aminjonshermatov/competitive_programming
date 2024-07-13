#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int r, g, b;
  std::string s;
  scan(r, g, b, s);
  if (s == "Red") {
    println(std::min(g, b));
  } else if (s == "Green") {
    println(std::min(r, b));
  } else {
    println(std::min(r, g));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}
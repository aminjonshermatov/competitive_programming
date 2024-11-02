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
  int n;
  scan(n);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    scan(as[i]);
  }
  std::map<int, int> prv;
  for (int i = 0; i < n; ++i) {
    print(prv.contains(as[i]) ? prv[as[i]] : -1);
    prv[as[i]] = i + 1;
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
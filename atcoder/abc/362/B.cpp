#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

int dist(int xa, int ya, int xb, int yb) {
  const auto dx = xa - xb;
  const auto dy = ya - yb;
  return dx * dx + dy * dy;
}

bool ok(int xa, int ya, int xb, int yb, int xc, int yc) {
  return dist(xa, ya, xb, yb) == (dist(xa, ya, xc, yc) + dist(xc, yc, xb, yb));
}

void solve() {
  int xa, ya, xb, yb, xc, yc;
  scan(xa, ya, xb, yb, xc, yc);
  if (ok(xa, ya, xb, yb, xc, yc) || ok(xa, ya, xc, yc, xb, yb) || ok(xb, yb, xc, yc, xa, ya)) {
    println("Yes");
  } else {
    println("No");
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
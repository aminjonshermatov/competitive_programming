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
  int n, a, b;
  Scan(n, a, b);

  const auto nEq = a + b;

  std::vector<int> as, bs;
  for (int i = nEq; i > 0; --i) {
    as.emplace_back(i);
  }
  for (int i = nEq + 1; i <= n; ++i) {
    as.emplace_back(i);
  }

  for (int i = a; i >= 1; --i) {
    bs.emplace_back(i);
  }
  for (int i = 0; i < b; ++i) {
    bs.emplace_back(nEq - i);
  }
  for (int i = nEq + 1; i <= n; ++i) {
    bs.emplace_back(i);
  }

  auto x = 0, y = 0;
  for (int i = 0; i < n; ++i) {
    x += as[i] > bs[i];
    y += as[i] < bs[i];
  }

  if (x == a && y == b) {
    Println("YES");
    for (int i = 0; i < n; ++i) {
      Print(as[i]);
    }
    Println();
    for (int i = 0; i < n; ++i) {
      Print(bs[i]);
    }
    Println();
  } else {
    Println("NO");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}

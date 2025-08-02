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
  int n, m;
  Scan(n, m);
  std::multiset<int> as;
  for (int i = 0; i < n; ++i) {
    int a;
    Scan(a);
    as.emplace(a);
  }
  for (int i = 0; i < m; ++i) {
    int b;
    Scan(b);
    if (as.contains(b)) {
      as.erase(as.find(b));
    }
  }
  for (auto a : as) {
    Print(a);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

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
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  std::set<std::pair<int, int>> xs;
  for (int i = 0; i < n; ++i) {
    while (!xs.empty() && xs.begin()->first < i) {
      as[xs.begin()->second] -= i - xs.begin()->second;
      xs.erase(xs.begin());
    }
    as[i] += xs.size();
    xs.emplace(as[i] + i, i);
  }
  while (!xs.empty()) {
    const auto i = xs.begin()->second;
    xs.erase(xs.begin());
    as[i] -= n - i - 1;
  }
  for (int i = 0; i < n; ++i) {
    Print(std::max(0, as[i]));
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

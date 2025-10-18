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
  int n, k;
  std::string s;
  Scan(n, k, s);

  std::map<std::string, int> qty;
  for (int i = 0; i + k <= n; ++i) {
    ++qty[s.substr(i, k)];
  }
  std::vector<std::pair<int, std::string>> xs;
  for (auto& [x, y] : qty) {
    xs.emplace_back(-y, x);
  }
  std::ranges::sort(xs);
  const auto x = -xs.front().first;
  Println(x);
  for (auto& [a, b] : xs) {
    if (a != -x) {
      break;
    }
    Print(b);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

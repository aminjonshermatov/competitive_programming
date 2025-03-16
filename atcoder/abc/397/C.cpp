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
  std::map<int, int> lhs, rhs;
  for (int i = 0; i < n; ++i) {
    ++rhs[as[i]];
  }
  std::size_t ret = 0;
  for (int i = 0; i + 1 < n; ++i) {
    if (--rhs[as[i]] == 0) {
      rhs.erase(as[i]);
    }
    ++lhs[as[i]];
    ret = std::max(ret, lhs.size() + rhs.size());
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

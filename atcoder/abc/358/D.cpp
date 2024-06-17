#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, m;
  scan(n, m);
  std::vector<int> as(n), bs(m);
  for (auto&& a : as) {
    scan(a);
  }
  for (auto&& b : bs) {
    scan(b);
  }
  std::ranges::sort(as);
  std::ranges::sort(bs);
  int64_t ret{};
  int j{};
  for (int i{}; i < n && j < m;) {
    while (as[i] < bs[j]) {
      ++i;
    }
    if (i < n) {
      assert(bs[j] <= as[i]);
      ret += as[i++];
      ++j;
    }
  }
  println(j == m ? ret : -1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
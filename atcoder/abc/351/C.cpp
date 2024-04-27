#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::vector<i64> as(n);
  for (auto&& a : as) {
    scan(a);
  }

  std::vector<i64> bs;
  for (auto&& a : as) {
    bs.emplace_back(a);
    while (bs.size() > 1u && bs[int(bs.size()) - 1] == bs[int(bs.size()) - 2]) {
      const auto z = bs.back();
      bs.pop_back();
      bs.pop_back();
      bs.emplace_back(z + 1);
    }
    dbg(bs);
  }
  println(bs.size());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
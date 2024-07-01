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
  i64 t;
  std::string s;
  scan(n, t, s);
  std::array<std::vector<i64>, 2> xs{};
  std::vector<i64> as(n);
  for (std::size_t i{}; i < s.size(); ++i) {
    scan(as[i]);
    xs[s[i] - '0'].emplace_back(as[i]);
  }
  for (auto&& x : xs) {
    std::ranges::sort(x);
  }

  dbg(xs);
  i64 tot{};
  for (auto&& x : xs[1]) {
    tot += int(std::ranges::upper_bound(xs[0], x + 2 * t) - std::ranges::lower_bound(xs[0], x));
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
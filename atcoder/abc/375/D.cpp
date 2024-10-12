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
  std::string s;
  scan(s);

  std::array<int, 26> sf{};
  for (auto c : s) {
    ++sf[c - 'A'];
  }
  std::array<int, 26> pf{};
  int64_t tot = 0;
  for (auto c : s) {
    --sf[c - 'A'];
    for (int x = 0; x < 26; ++x) {
      tot += pf[x] * 1LL * sf[x];
    }
    ++pf[c - 'A'];
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
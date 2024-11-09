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
  int n;
  std::string s;
  scan(n, s);

  using i64 = int64_t;
  std::vector<i64> pf(n);
  for (i64 i = 0; i < n; ++i) {
    pf[i] = (i > 0 ? pf[i - 1] : 0) + (i + 1) * (s[i] - '0');
  }
  dbg(pf);
  std::string ret;
  i64 off = 0;
  for (int i = n - 1; off > 0 || i >= 0; --i) {
    auto cur = off;
    if (i >= 0) {
      cur += pf[i];
    }
    ret.push_back('0' + (cur % 10));
    off = cur / 10;
  }
  std::ranges::reverse(ret);
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
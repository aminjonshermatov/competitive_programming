#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  i64 n;
  scan(n);
  --n;

  if (n == 0) {
    println(0);
    return;
  }

  std::array<i64, 19> pw10{};
  pw10[0] = 1;
  for (int i = 1; i < pw10.size(); ++i) {
    pw10[i] = pw10[i - 1] * 10;
  }

  for (int len = 1;; ++len) {
    const auto me = i64{9} * pw10[(len - 1) / 2];
    dbg(len, me, n);
    std::cerr.flush();
    if (me < n) {
      n -= me;
      continue;
    }
    std::string ret(len, '#');
    dbg(n, len);
    for (int i = 0; i <= (len - 1) / 2; ++i) {
      for (char c = i == 0 ? '1' : '0'; c <= '9'; ++c) {
        const auto rest = pw10[(len - 1) / 2 - i];
        if (rest < n) {
          n -= rest;
        } else {
          ret[i] = ret[len - 1 - i] = c;
          break;
        }
      }
    }
    println(ret);
    return;
  }
  assert(false);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  freopen("../../input.txt", "r", stdin);
#endif

  solve();
}
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
  int n, k;
  std::string s;
  scan(n, k, s);

  int ret = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'X') {
      continue;
    }
    int j = i;
    while (j + 1 < n && s[j + 1] == 'O' && j - i + 1 < k) {
      ++j;
    }
    dbg(i,j);
    ret += j - i + 1 == k;
    i = j;
  }
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
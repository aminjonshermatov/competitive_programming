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
  int n, m;
  scan(n, m);
  std::vector<int> ls(n), rs(n);
  for (int i = 0; i < n; ++i) {
    scan(ls[i], rs[i]);
  }
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return ls[i] == ls[j] ? rs[i] > rs[j] : ls[i] > ls[j];
  });
  int ptr = 0, min = m + 1;
  int64_t tot = 0;
  for (int i = m; i >= 1; --i) {
    while (ptr < n && ls[ord[ptr]] >= i) {
      min = std::min(min, rs[ord[ptr++]]);
    }
    tot += min - i;
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
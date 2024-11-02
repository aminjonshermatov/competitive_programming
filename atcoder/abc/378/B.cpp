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
  scan(n);
  std::vector<int> qs(n), rs(n);
  for (int i = 0; i < n; ++i) {
    scan(qs[i], rs[i]);
  }
  int q;
  scan(q);
  while (q-- > 0) {
    int t, d;
    scan(t, d);
    --t;
    auto x = d % qs[t];
    dbg(x);
    d += (rs[t] - x + qs[t]) % qs[t];
    println(d);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
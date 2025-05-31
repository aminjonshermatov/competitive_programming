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
  std::string s;
  Scan(n, s);

  std::vector pf(n, 0);
  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      pf[i] += pf[i - 1];
    }
    pf[i] += s[i] - '0';
  }
  auto ret = n + 1;
  auto best = -1;
  for (int i = 0; i < n; ++i) {
    best = std::max(best, i - pf[i] * 2);
    ret = std::min(ret, i - pf[i] * 2 - best + pf.back());
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}

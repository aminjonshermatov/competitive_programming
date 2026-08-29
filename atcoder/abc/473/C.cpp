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
  int n, k;
  Scan(n, k);
  std::vector qty(k, 0);
  for (int i = 0; i < n; ++i) {
    int c;
    Scan(c);
    ++qty[c - 1];
  }

  std::vector suf(k, 0);
  suf[k - 1] = qty[k - 1];
  for (int i = k - 2; i >= 0; --i) {
    suf[i] = std::max(suf[i + 1], qty[i]);
  }
  auto ret = 0;
  for (int i = 0, p = 0; i < k; ++i) {
    const auto s = i + 1 < k ? suf[i + 1] : 0;
    ret += (qty[i] + 1) >= std::max(p, s);
    p = std::max(p, qty[i]);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

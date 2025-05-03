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
  Scan(n);
  std::vector<std::string> s(n), t(n);
  for (int i = 0; i < n; ++i) {
    Scan(s[i]);
  }
  for (int i = 0; i < n; ++i) {
    Scan(t[i]);
  }

  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  auto ret = kInf;
  for (int _ = 0; _ < 4; ++_) {
    auto loc = _;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        loc += static_cast<int>(s[i][j] != t[i][j]);
      }
    }
    ret = std::min(ret, loc);
    auto ns = s;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        ns[j][n - i - 1] = s[i][j];
      }
    }
    std::swap(ns, s);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

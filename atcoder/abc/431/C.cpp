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
  int n, m, k;
  Scan(n, m, k);
  std::vector<int> hs(n), bs(m);
  for (int i = 0; i < n; ++i) {
    Scan(hs[i]);
  }
  for (int i = 0; i < m; ++i) {
    Scan(bs[i]);
  }

  std::ranges::sort(hs);
  std::ranges::sort(bs);
  for (int i = 0, j = 0; i < n && j < m; ++i, ++j) {
    while (j < m && hs[i] > bs[j]) {
      ++j;
    }
    if (j < m && i + 1 >= k) {
      Println("Yes");
      return;
    }
  }
  Println("No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

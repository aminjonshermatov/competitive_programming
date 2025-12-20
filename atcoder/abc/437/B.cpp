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
  int n, m, q;
  Scan(n, m, q);
  std::vector g(n, std::vector(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Scan(g[i][j]);
    }
  }

  std::vector<int> bs(q);
  for (int i = 0; i < q; ++i) {
    Scan(bs[i]);
  }
  std::ranges::sort(bs);
  auto ret = 0;
  for (int i = 0; i < n; ++i) {
    auto loc = 0;
    for (int j = 0; j < m; ++j) {
      loc += std::ranges::binary_search(bs, g[i][j]);
    }
    ret = std::max(ret, loc);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

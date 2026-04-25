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
  int n, m;
  Scan(n, m);
  std::vector g(n, std::string(m, '#'));
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  auto ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int il = 1; il <= n - i; ++il) {
        for (int jl = 1; jl <= m - j; ++jl) {
          auto ok = true;
          for (int ii = i; ii < i + il && ok; ++ii) {
            for (int jj = j; jj < j + jl && ok; ++jj) {
              ok &= g[ii][jj] == g[i + i + il - 1 - ii][j + j + jl - 1 - jj];
            }
          }
          ret += ok;
        }
      }
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

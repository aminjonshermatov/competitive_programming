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
  std::vector deg(n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    ++deg[u], ++deg[v];
  }

  std::vector ret(n, 0LL);
  for (int i = 0; i < n; ++i) {
    const auto x = n - deg[i] - 1;
    ret[i] = x * 1LL * (x - 1) * (x - 2) / 6;
  }
  for (int i = 0; i < n; ++i) {
    Print(ret[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

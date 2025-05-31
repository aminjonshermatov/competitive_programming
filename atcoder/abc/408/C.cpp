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
  std::vector pf(n, 0);
  for (int i = 0; i < m; ++i) {
    int l, r;
    Scan(l, r);
    --l, --r;
    ++pf[l];
    if (r + 1 < n) {
      --pf[r + 1];
    }
  }
  std::partial_sum(pf.begin(), pf.end(), pf.begin());
  dbg(pf);
  Println(std::ranges::min(pf));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

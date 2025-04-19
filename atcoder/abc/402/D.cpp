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
  std::vector<int> as(m), bs(m);
  for (int i = 0; i < m; ++i) {
    Scan(as[i], bs[i]);
  }

  auto ret = m * 1LL * (m - 1) / 2;
  std::map<int, int> qty;
  for (int i = 0; i < m; ++i) {
    ret -= qty[(as[i] + bs[i]) % n]++;
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

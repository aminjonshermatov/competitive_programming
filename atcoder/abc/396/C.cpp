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
  std::vector<int64_t> bs(n), ws(m);
  for (int i = 0; i < n; ++i) {
    Scan(bs[i]);
  }
  for (int i = 0; i < m; ++i) {
    Scan(ws[i]);
  }
  std::ranges::sort(bs, std::greater<>{});
  std::ranges::sort(ws, std::greater<>{});
  int64_t ret = 0, cur = 0;
  for (int i = 0; i < n; ++i) {
    cur += bs[i] + std::max<int64_t>(0, i < m ? ws[i] : 0);
    ret = std::max(ret, cur);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

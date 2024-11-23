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
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  int ret = 0;
  auto relax = [&](const std::vector<int>& xs) {
    std::vector<int> last(n + 1, -1);
    for (int l = 0, r = 0; r < xs.size(); ++r) {
      if (xs[r] == -1) {
        l = r + 1;
      } else {
        if (last[xs[r]] != -1) {
          l = std::max(l, last[xs[r]] + 1);
        }
        ret = std::max(ret, (r - l + 1) * 2);
        last[xs[r]] = r;
      }
    }
  };
  for (int beg = 0; beg < 2; ++beg) {
    std::vector<int> xs(n / 2, -1);
    for (int i = beg; i + 1 < n; i += 2) {
      if (as[i] == as[i + 1]) {
        xs[i / 2] = as[i];
      }
    }
    relax(xs);
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

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
  std::vector<int> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  for (int i = 0; i < n; ++i) {
    Scan(bs[i]);
  }

  auto work = [&] {
    auto loc = 0LL;
    std::multiset<int> xs(as.begin(), as.end());
    for (int i = 0; i < n; ++i) {
      auto it = xs.lower_bound(m - bs[i]);
      int a = m, b = 2 * m;
      if (it != xs.begin()) {
        a = *std::prev(it);
      }
      if (it != xs.end()) {
        b = *it;
      }
      if (a + bs[i] < b + bs[i] - m) {
        xs.erase(std::prev(it));
        loc += a + bs[i];
      } else {
        xs.erase(it);
        loc += b + bs[i] - m;
      }
    }
    return loc;
  };

  std::ranges::sort(bs);
  auto ret = work();
  std::ranges::sort(bs, std::greater{});
  ret = std::min(ret, work());
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}

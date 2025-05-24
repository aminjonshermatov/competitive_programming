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
  std::vector as(2 * n, int64_t{});
  for (int i = 0; i < n * 2; ++i) {
    Scan(as[i]);
  }

  auto pq = std::priority_queue<int64_t>{};
  int64_t tot = 0;
  for (int i = 0; i < 2 * n; ++i) {
    if (i % 2 == 1) {
      tot += pq.top();
      pq.pop();
    }
    pq.emplace(as[i]);
  }
  Println(tot);
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

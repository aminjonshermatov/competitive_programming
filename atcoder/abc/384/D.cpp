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
  int64_t s;
  Scan(n, s);
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  const auto tot = std::accumulate(as.begin(), as.end(), int64_t{});
  const auto rem = s % tot;
  const auto rem2 = rem + tot;
  if (rem == 0) {
    Println("Yes");
    return;
  }
  std::set<int64_t> seen;
  // x + y = rem
  // y = rem - x
  seen.emplace(0);
  for (int64_t cur = 0; auto a : as) {
    cur += a;
    if (cur == rem || cur == rem2) {
      Println("Yes");
      return;
    }
    seen.emplace(cur);
  }
  for (int64_t cur = 0; auto a : as | std::ranges::views::reverse) {
    cur += a;
    if (cur == rem || cur == rem2 || seen.contains(rem - cur) || seen.contains(rem2 - cur)) {
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

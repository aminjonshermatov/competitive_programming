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
  int n, k;
  Scan(n, k);
  std::vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  dbg("fuck");
  const auto maxA = std::ranges::max(as);
  std::vector<int> cnt(maxA + 1, 0);
  for (int i = 0; i < n; ++i) {
    ++cnt[as[i]];
  }
  std::vector<int> ret(maxA + 1, 0);
  for (int i = 1; i <= maxA; ++i) {
    int c = 0;
    for (int j = i; j <= maxA; j += i) {
      c += cnt[j];
    }
    if (c >= k) {
      for (int j = i; j <= maxA; j += i) {
        ret[j] = std::max(ret[j], i);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    Print(ret[as[i]]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

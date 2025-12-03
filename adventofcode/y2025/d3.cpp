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
  constexpr int kLim = 12;
  auto ret = 0LL;
  for (std::string s;; s.clear()) {
    std::cin >> s;
    if (s.empty()) {
      break;
    }
    std::array<int64_t, kLim + 1> dp{};
    for (auto c : s) {
      auto ndp = dp;
      for (int lst = 0; lst < kLim; ++lst) {
        ndp[lst + 1] = std::max(ndp[lst + 1], dp[lst] * 10 + c - '0');
      }
      std::swap(dp, ndp);
    }
    ret += dp[kLim];
  }
  dbg(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

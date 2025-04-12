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
  std::vector<int64_t> as(n + 1);
  std::fill(as.begin(), std::next(as.begin(), std::min(n + 1, k)), 1);
  int64_t acc = k;
  constexpr int64_t kMod = 1E9;
  for (int i = k; i <= n; ++i) {
    as[i] = acc;
    acc = ((acc - as[i - k] + kMod) % kMod + kMod) % kMod;
    acc = ((acc + as[i]) % kMod + kMod) % kMod;
  }
  Println(as[n]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

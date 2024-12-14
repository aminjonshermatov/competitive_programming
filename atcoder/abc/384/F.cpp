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

  constexpr std::size_t kB = 26;
  std::array<int64_t, kB + 1> ds{};
  for (int64_t b = 0; b < kB; ++b) {
    const auto mod = 1LL << b;
    std::vector<int64_t> sum(mod), qty(mod);
    for (auto a : as) {
      const auto oth = ((-a % mod) + mod) % mod;
      sum[oth] += a;
      qty[oth] += 1;
      ds[b] += qty[a % mod] * a + sum[a % mod];
    }
  }
  int64_t ret = 0;
  for (std::size_t i = 0; i < kB; ++i) {
    ret += (ds[i] - ds[i + 1]) >> i;
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

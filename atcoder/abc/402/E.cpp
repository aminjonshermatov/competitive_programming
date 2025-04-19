#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }


using Ld = long double;
constexpr Ld kEps = 1E-5;

constexpr auto Imax(Ld& a, const Ld& b) noexcept {
  if (b - a > kEps) {
    a = b;
  }
}

void Solve() {
  int n, x;
  Scan(n, x);
  std::vector<int> ss(n), cs(n);
  std::vector<Ld> ps(n);
  for (int i = 0; i < n; ++i) {
    Scan(ss[i], cs[i], ps[i]);
    ps[i] /= 100;
  }

  std::vector dp(1 << n, std::vector(x + 1, Ld{0}));
  for (int m = (1 << n) - 1; m >= 0; --m) {
    for (auto tmp = ~m & ((1 << n) - 1); tmp > 0;) {
      const auto i = std::__lg(tmp);
      for (int s = x - cs[i]; s >= 0; --s) {
        dp[m][s] = std::max(dp[m][s], (dp[m | (1 << i)][s + cs[i]] + ss[i]) * ps[i] + dp[m][s + cs[i]] * (Ld{1} - ps[i]));
        // Imax(dp[m][s], (dp[m | (1 << i)][s + cs[i]] + ss[i]) * ps[i] + dp[m][s + cs[i]] * (Ld{1} - ps[i]));
      }
      tmp ^= 1 << i;
    }
  }
  Ld ret = 0.;
  for (int s = 0; s <= x; ++s) {
    // Imax(ret, dp[0][s]);
    ret = std::max(ret, dp[0][s]);
  }
  std::cout << std::fixed << std::setprecision(15) << ret << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

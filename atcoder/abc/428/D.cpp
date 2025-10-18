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
  int64_t c, d;
  Scan(c, d);

  auto len = [](int64_t x) {
    auto ret = 0;
    for (; x > 0; ++ret, x /= 10) { }
    return ret;
  };

  int64_t ret = 0;
  for (int64_t prv = 1, pw10 = 10; prv <= d; pw10 *= 10) {
    const auto nxt = std::min(d + 1, pw10 - c);
    if (prv >= nxt) {
      continue;
    }
    // 1 <= f(c, c + x) <= d
    // 1 <= c * 10^p + c + x <= d
    // 1 <= c * (10^p + 1) + x <= d

    // let: y
    // 1 <= y^2 - c * (10^p + 1) <= d
    // y^2 - c * (10^p + 1) >= 1
    //   y^2 >= c * (10^p + 1) + 1
    // y^2 - c * (10^p + 1) <= d
    //   y^2 <= c * (10^p + 1) + d
    const auto val = c * (pw10 + 1);
    auto f = [](int64_t z) {
      int64_t x = std::sqrt(z);
      while (x * x < z) ++x;
      return x;
    };

    ret += f(val + nxt) - f(val + prv);
    prv = nxt;
  }
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

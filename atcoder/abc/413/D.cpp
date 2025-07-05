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

  std::ranges::sort(as, [&](const int a, const int b) {
    return std::abs(a) < std::abs(b);
  });
  if (std::abs(as.front()) == std::abs(as.back())) {
    const auto neg = std::ranges::count_if(as, [](const auto a) { return a < 0; });
    const auto pos = n - neg;
    if (n % 2 == 0) {
      Println(neg == 0 || pos == 0 || pos == neg ? "Yes" : "No");
    } else {
      Println(neg == 0 || pos == 0 || std::abs(pos - neg) == 1 ? "Yes" : "No");
    }
    return;
  }
  // as[i]/as[i-1] = as[i+1]/as[i]
  for (int i = 1; i + 1 < n; ++i) {
    if (as[i] * 1LL * as[i] != as[i - 1] * 1LL * as[i + 1]) {
      Println("No");
      return;
    }
  }
  Println("Yes");
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

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
  std::vector as(1 << n, 0);
  for (int i = 0; i < (1 << n); ++i) {
    Scan(as[i]);
  }

  auto dq = [&](auto&& self, int l, int r) -> std::vector<int> {
    if (r - l == 1) {
      return {as[l]};
    }
    const auto mid = std::midpoint(l, r);
    auto a = self(self, l, mid);
    auto b = self(self, mid, r);
    if (a[0] > b[0]) {
      std::swap(a, b);
    }
    a.insert(a.end(), b.begin(), b.end());
    return a;
  };
  for (const auto a : dq(dq, 0, 1 << n)) {
    Print(a);
  }
  Println();
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

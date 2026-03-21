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
  int64_t k;
  Scan(n, k);
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  if (n == 1) {
    Println(0);
    return;
  }

  for (int i = 0; i < n; ++i) {
    if ((as[i] %= k) < 0) {
      as[i] += k;
    }
  }
  auto xs = std::multiset(as.begin(), as.end());
  auto ret = *xs.rbegin() - *xs.begin();
  for (int _ = 0; _ < n; ++_) {
    const auto x = *xs.begin();
    xs.erase(xs.begin());
    xs.emplace(x + k);
    ret = std::min(ret, *xs.rbegin() - *xs.begin());
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

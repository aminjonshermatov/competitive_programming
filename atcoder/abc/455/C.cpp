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
  std::map<int, int> qty;
  for (int i = 0; i < n; ++i) {
    int x;
    Scan(x);
    ++qty[x];
  }
  std::vector<std::pair<int64_t, int>> xs;
  for (auto [kk, v] : qty) {
    xs.emplace_back(-kk * 1LL * v, kk);
  }
  std::ranges::sort(xs);
  for (int i = 0; i < std::min<int>(k, xs.size()); ++i) {
    auto old = std::exchange(qty[xs[i].second], 0);
    qty[0] += old;
  }
  auto ret = 0LL;
  for (auto [kk, v] : qty) {
    ret += kk * 1LL * v;
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

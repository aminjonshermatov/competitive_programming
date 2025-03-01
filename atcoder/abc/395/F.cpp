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
  int64_t x;
  Scan(n, x);
  std::vector<int64_t> upper(n), down(n);
  for (auto i = 0; i < n; ++i) {
    Scan(upper[i], down[i]);
  }

  int64_t cost = 0;
  auto normalize = [&](auto& ts) {
    std::set<std::pair<int, int>> xs;
    for (int i = 0; i < n; ++i) {
      xs.emplace(ts[i], i);
    }
    while (!xs.empty()) {
      const auto [_, i] = *xs.begin();
      xs.erase(xs.begin());
      if (i > 0 && ts[i - 1] > ts[i] + x) {
        cost += ts[i - 1] - ts[i] - x;
        xs.erase(std::pair(ts[i - 1], i - 1));
        xs.emplace(ts[i - 1] = ts[i] + x, i - 1);
      }
      if (i + 1 < n && ts[i + 1] > ts[i] + x) {
        cost += ts[i + 1] - ts[i] - x;
        xs.erase(std::pair(ts[i + 1], i + 1));
        xs.emplace(ts[i + 1] = ts[i] + x, i + 1);
      }
    }
  };

  normalize(upper);
  normalize(down);

  auto h = std::numeric_limits<int64_t>::max() / 2;
  for (int i = 0; i < n; ++i) {
    h = std::min(h, upper[i] + down[i]);
  }
  for (int i = 0; i < n; ++i) {
    cost += upper[i] + down[i] - h;
  }
  Println(cost);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

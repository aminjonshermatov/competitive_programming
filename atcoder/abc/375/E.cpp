#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n;
  scan(n);
  std::vector<int> as(n), bs(n);
  for (std::size_t i = 0; i < n; ++i) {
    scan(as[i], bs[i]);
  }
  const auto [q, r] = std::div(std::accumulate(bs.begin(), bs.end(), 0), 3);
  if (r != 0) {
    println(-1);
    return;
  }
  constexpr auto inf = std::numeric_limits<int>::max() / 3;
  std::vector cache(n, std::vector(q + 1, std::vector(q + 1, -1)));
  auto dp = [&](auto&& self, int i, int x, int y) -> int {
    if (std::clamp(x, 0, q) != x || std::clamp(y, 0, q) != y) {
      return inf;
    }
    if (i >= n) {
      return x == q && y == q ? 0 : inf;
    }
    auto& loc = cache[i][x][y];
    if (loc != -1) {
      return loc;
    }
    loc = inf;
    for (int me = 1; me <= 3; ++me) {
      auto nx = x, ny = y;
      if (me == 1) {
        nx += bs[i];
      } else if (me == 2) {
        ny += bs[i];
      }
      loc = std::min(loc, self(self, i + 1, nx, ny) + (as[i] != me));
    }
    return loc;
  };
  const auto ret = dp(dp, 0, 0, 0);
  println(ret == inf ? -1 : ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
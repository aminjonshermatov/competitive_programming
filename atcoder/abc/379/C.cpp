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
  int n, m;
  scan(n, m);
  using i64 = int64_t;
  std::vector<i64> xs(m), as(m);
  for (int i = 0; i < m; ++i) {
    scan(xs[i]);
  }
  i64 tot = 0;
  for (int i = 0; i < m; ++i) {
    scan(as[i]);
    tot += as[i];
  }
  if (tot != n) {
    println(-1);
    return;
  }
  std::vector<int> ord(m);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return xs[i] < xs[j];
  });

  i64 ret = 0, sum = 0, acc = 0;
  for (auto id : ord) {
    if (sum < xs[id] - 1) {
      println(-1);
      return;
    }
    acc += as[id] * (xs[id] - 1);
    sum += as[id];
  }
  println(n * 1LL * (n - 1) / 2 - acc);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
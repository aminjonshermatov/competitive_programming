#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  int n;
  scan(n);
  std::array<std::vector<int>, 2> as{}, bs{};
  for (auto&& i : std::views::iota(0, n)) {
    int x, y;
    scan(x, y);
    // max(|a|, |b|) -> 1/2(||a|+|b||+||a|-|b||)
    // 2*max(|a+b|, |a-b|) -> 1/2(|a|+|b|)
    // max(|a+b|, |a-b|) -> 1/4(|a|+|b|)
    as[(x + y) % 2].emplace_back(x + y);
    bs[(x + y) % 2].emplace_back(x - y);
  }

  auto f = [](std::vector<int>& xs) -> i64 {
    i64 loc = 0;
    assert(std::ranges::is_sorted(xs));
    const auto cum = std::accumulate(xs.begin(), xs.end(), i64{});
    i64 lhs = 0;
    for (std::size_t i{}; i < xs.size(); ++i) {
      lhs += xs[i];
      loc += xs[i] * 1LL * (i + 1) - lhs + cum - lhs - (xs.size() - i - 1) * 1LL * xs[i];
    }
    return loc;
  };

  i64 tot = 0;
  for (auto&& parity : std::views::iota(0, 2)) {
    std::ranges::sort(as[parity]);
    std::ranges::sort(bs[parity]);

    tot += f(as[parity]);
    tot += f(bs[parity]);
  }
  println(tot / 4);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
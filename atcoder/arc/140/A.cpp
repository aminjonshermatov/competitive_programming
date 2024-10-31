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
  int n, k;
  std::string s;
  scan(n, k, s);

  auto work = [&](int p) -> int {
    std::vector cnt(p, std::vector(26, 0));
    for (int i = 0; i < n; ++i) {
      ++cnt[i % p][s[i] - 'a'];
    }
    int curK = 0;
    for (int i = 0, q = n / p; i < p; ++i) {
      curK += q - std::ranges::max(cnt[i]);
    }
    return curK <= k ? p : n;
  };

  int ret = n;
  for (int d = 1; d * d <= n; ++d) {
    const auto [q, r] = std::div(n, d);
    if (r != 0) {
      continue;
    }
    ret = std::min(ret, work(d));
    ret = std::min(ret, work(q));
  }
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
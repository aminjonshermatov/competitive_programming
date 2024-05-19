#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n;
  scan(n);
  std::vector<int> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    scan(as[i], bs[i]);
  }

  const auto all = (1 << n) - 1;
  std::vector<int> cache(1 << n, -1);
  auto dp = [&](auto&& self, int used) -> bool {
    if (__builtin_popcount(all ^ used) < 2) {
      return false;
    }
    auto& loc = cache[used];
    if (loc != -1) {
      return loc;
    }
    loc = 0;
    std::vector<int> ids;
    for (auto tmp = all ^ used; tmp > 0;) {
      const auto id = std::__lg(tmp);
      ids.emplace_back(id);
      tmp ^= 1 << id;
    }
    for (std::size_t i{}; i < ids.size(); ++i) {
      for (std::size_t j{}; j < i; ++j) {
        if (as[ids[i]] == as[ids[j]] || bs[ids[i]] == bs[ids[j]]) {
          loc |= !self(self, used | (1 << ids[i]) | (1 << ids[j]));
        }
      }
    }
    return loc;
  };
  println(dp(dp, 0) ? "Takahashi" : "Aoki");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
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
  std::string s;
  Scan(n, s);
  s = "0" + s;

  std::vector cache(1 << n, -1);
  const auto all = (1 << n) - 1;
  auto dfs = [&](auto&& self, int m) -> bool {
    if (s[m] == '1') {
      return false;
    }
    if (m == all) {
      return true;
    }
    auto& loc = cache[m];
    if (loc != -1) {
      return loc;
    }
    loc = 0;
    for (auto tmp = ~m & all; tmp > 0;) {
      const auto i = std::__lg(tmp);
      if (s[m | (1 << i)] == '0' || (m | (1 << i)) == all) {
        loc |= self(self, m | (1 << i));
      }
      tmp ^= 1 << i;
    }
    return loc;
  };
  Println(dfs(dfs, 0) ? "Yes" : "No");
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}

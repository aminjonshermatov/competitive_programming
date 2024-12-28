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
  int k;
  std::string s, t;
  Scan(k, s, t);

  const auto n = int(s.size());
  const auto m = int(t.size());

  using T = std::tuple<int, int, int>;
  std::set<T> dp;
  dp.emplace(0, 0, 0);
  for (int pos = 0; pos < n; ++pos) {
    std::set<T> ndp;
    for (const auto [ins, rem, upd] : dp) {
      const auto used = ins + rem + upd;
      const auto match = pos + ins - rem;
      if (match == m) {
        const auto moreRem = n - pos;
        if (used + moreRem <= k) {
          Println("Yes");
        }
        continue;
      }
      if (s[pos] == t[match]) {
        ndp.emplace(ins, rem, upd);
      }
      if (used < k) {
        if (ndp.contains(T{ins}))
      }
    }
    std::swap(dp, ndp);
  }
  Println("No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

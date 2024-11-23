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
  std::string s;
  Scan(s);
  const auto n = int(s.size());
  if (n % 2 == 1) {
    Println("No");
    return;
  }
  std::map<char, int> cnt;
  for (int i = 0; i < n; ++i) {
    ++cnt[s[i]];
  }
  bool ok = true;
  for (int i = 1; i <= n / 2; ++i) {
    ok &= s[2 * i - 1] == s[2 * i - 2];
  }
  for (auto& [x, y] : cnt) {
    ok &= y == 2;
  }
  Println(ok ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

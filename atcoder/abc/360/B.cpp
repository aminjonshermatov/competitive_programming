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
  std::string s, t;
  scan(s, t);
  const auto n = static_cast<int>(s.size());
  const auto m = static_cast<int>(t.size());

  for (int c = 1; c < n; ++c) {
    for (int w = c; w < n; ++w) {
      bool ok = true;
      int i{}, j{};
      for (; i + c - 1 < n && j < m && ok; i += w) {
        ok &= s[i + c - 1] == t[j++];
      }
      if (ok && j == m && i + c - 1 >= n) {
        println("Yes");
        return;
      }
    }
  }

  println("No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
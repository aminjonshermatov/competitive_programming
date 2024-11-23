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
  if (n % 2 == 1) {
    const auto mid=  n / 2;
    bool ok = s[mid] == '/';
    for (int i = 0; i < mid; ++i) {
      ok &= s[i] == '1';
    }
    for (int i = mid + 1; i < n; ++i) {
      ok &= s[i] == '2';
    }
    Println(ok ? "Yes" : "No");
  } else {
    Println("No");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

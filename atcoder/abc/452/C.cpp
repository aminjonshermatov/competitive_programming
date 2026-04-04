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
  Scan(n);
  std::vector<int> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i], bs[i]);
  }
  int m;
  Scan(m);
  std::vector<std::string> ss(m);
  for (int i = 0; i < m; ++i) {
    Scan(ss[i]);
  }

  std::vector has(26, std::vector(n, false));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (ss[i].size() != as[j]) {
        continue;
      }
      for (auto c : ss[i]) {
        has[c - 'a'][j] = has[c - 'a'][j] || ss[i][bs[j] - 1] == c;
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    auto f = false;
    if (ss[i].size() == n) {
      f = true;
      for (int j = 0; j < n; ++j) {
        f &= has[ss[i][j] - 'a'][j];
      }
    }
    Print(f ? "Yes" : "No");
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

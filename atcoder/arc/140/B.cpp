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
  int n;
  std::string s;
  scan(n, s);

  int a = 0;
  std::multiset<int> may;
  for (int i = 0; i + 2 < n; ++i) {
    if (s[i] == 'A' && s[i + 1] == 'R' && s[i + 2] == 'C') {
      int c = 0;
      dbg(i);
      while (i + 3 < n && s[i + 3] == 'C') {
        ++c;
        ++i;
      }
      may.emplace(std::min(a, c));
      i += 2;
      a = 0;
    } else if (s[i] == 'A') {
      ++a;
    } else {
      a = 0;
    }
  }
  int ret = 0;
  dbg(may);
  for (int i = 0; !may.empty(); ++i, ++ret) {
    if (i % 2 == 0) {
      auto it = std::prev(may.end());
      const auto x = *it;
      may.erase(it);
      if (x > 0) {
        may.emplace(x - 1);
      }
    } else {
      may.erase(may.begin());
    }
  }
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
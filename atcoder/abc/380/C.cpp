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
  int n, k;
  std::string s;
  Scan(n, k, s);

  std::vector<std::pair<int, int>> xs;
  for (int i = 0; i < n && xs.size() < k; ++i) {
    if (s[i] != '1') {
      continue;
    }
    auto j = i;
    while (j + 1 < n && s[j + 1] == '1') {
      ++j;
    }
    xs.emplace_back(i, j);
    i = j;
  }
  s.erase(s.begin() + xs.back().first, s.begin() + xs.back().second + 1);
  s.insert(xs[xs.size() - 2].second + 1, xs.back().second - xs.back().first + 1, '1');
  Println(s);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

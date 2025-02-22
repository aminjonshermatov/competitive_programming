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

  std::string stk;
  for (auto c : s) {
    stk.push_back(c);
    auto cnt = 0;
    while (stk.size() > 1 && stk[stk.size() - 2] == 'W' && stk[stk.size() - 1] == 'A') {
      ++cnt;
      stk.pop_back();
      stk.pop_back();
      stk.push_back('A');
    }
    stk.append(cnt, 'C');
  }
  Println(stk);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

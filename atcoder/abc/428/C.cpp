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
  int q;
  Scan(q);

  std::vector<std::pair<int, int>> stk;
  auto bal = 0;
  while (q-- > 0) {
    char cmd;
    Scan(cmd);

    if (cmd == '1') {
      char c;
      Scan(c);
      const auto x = c == '(' ? +1 : -1;;
      bal += x;
      stk.emplace_back(stk.empty() ? x : std::min(stk.back().first, bal), x);
    } else {
      bal -= stk.back().second;
      stk.pop_back();
    }
    Println(stk.empty() || (bal == 0 && stk.back().first >= 0) ? "Yes" : "No");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

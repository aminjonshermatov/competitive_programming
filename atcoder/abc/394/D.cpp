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
    if (!stk.empty() && ((stk.back() == '(' && c == ')') ||
                         (stk.back() == '<' && c == '>') ||
                         (stk.back() == '[' && c == ']'))) {
      stk.pop_back();
    } else {
      stk.push_back(c);
    }
  }
  dbg(stk);
  Println(stk.empty() ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

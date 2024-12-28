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
  std::map<int, int> cnt;
  for (int i = 0; i < 4; ++i) {
    int x;
    Scan(x);
    ++cnt[x];
  }
  // 3 2
  // +1  0
  //  0 +1
  auto ok = cnt.size() == 2;
  ok &= (cnt.begin()->second == 2 && cnt.rbegin()->second == 2) || (cnt.begin()->second == 1 && cnt.rbegin()->second == 3) || (cnt.begin()->second == 3 && cnt.rbegin()->second == 1);
  Println(ok ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

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
  std::vector<int> as(n);
  std::map<int, int> cnt;
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
    ++cnt[as[i]];
  }
  auto ret = -2;
  for (int i = 0; i < n; ++i) {
    if (cnt[as[i]] == 1 && (ret == -2 || as[i] > as[ret])) {
      ret = i;
    }
  }
  Println(ret + 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

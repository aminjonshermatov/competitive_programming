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

  std::vector prv(10, std::vector(n, std::pair(-1, 01)));
  std::queue<std::pair<int, int>> que;
  for (int d = 1; d < 10; ++d) {
    if (d % n == 0) {
      Println(d);
      return;
    }
    prv[d][d % n] = {0, 0};
    que.emplace(d % n, d);
  }
  while (!que.empty()) {
    auto [num, lst] = que.front();
    que.pop();
    if (num == 0) {
      std::string s;
      for (;;) {
        s.push_back('0' + lst);
        std::tie(num, lst) = prv[lst][num];
        if (num == 0) {
          break;
        }
      }
      std::ranges::reverse(s);
      Println(s);
      return;
    }

    for (auto d = std::max<int>(1, lst); d < 10; ++d) {
      const auto nNum = ((num * 10 + d) % n + n) % n;
      if (prv[d][nNum].first == -1) {
        prv[d][nNum] = {num, lst};
        que.emplace(nNum, d);
      }
    }
  }
  Println(-1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

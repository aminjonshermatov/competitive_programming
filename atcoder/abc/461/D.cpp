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
  int n, m, k;
  Scan(n, m, k);
  std::vector<std::string> g(n);
  for (int i = 0; i < n; ++i) {
    Scan(g[i]);
  }

  std::vector data(n * m + 1, 0), when(n * m + 1, -1);
  auto timer = 0;
  auto get = [&](int key) {
    if (key < 0 || key > n * m || when[key] != timer) {
      return 0;
    }
    return data[key];
  };
  auto set = [&](int key, int val) {
    if (key < 0 || key > n * m) {
      return;
    }
    when[key] = timer;
    data[key] = val;
  };

  auto ret = 0LL;
  for (int l = 0; l < m; ++l) {
    std::vector byR(n, 0);
    for (int r = l; r < m; ++r) {
      ++timer;
      set(0, 1);
      auto cur = 0;
      for (int i = 0; i < n; ++i) {
        byR[i] += g[i][r] - '0';
        cur += byR[i];
        ret += get(cur - k);
        set(cur, get(cur) + 1);
      }
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

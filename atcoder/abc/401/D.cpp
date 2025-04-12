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

  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dpPf(n + 2, std::array{0, 0}), dpSf(n + 2, std::array{0, 0});
  for (int i = 1; i <= n; ++i) {
    if (s[i - 1] == 'o') {
      dpPf[i][0] = dpPf[i - 1][1] + 1;
      dpPf[i][1] = -kInf;
    } else if (s[i - 1] == '.') {
      dpPf[i][0] = -kInf;
      dpPf[i][1] = std::max(dpPf[i - 1][0], dpPf[i - 1][1]);
    } else {
      dpPf[i][0] = dpPf[i - 1][1] + 1;
      dpPf[i][1] = std::max(dpPf[i - 1][0], dpPf[i - 1][1]);
    }
    if (s[n - i] == 'o') {
      dpSf[n - i + 1][0] = dpSf[n - i + 2][1] + 1;
      dpSf[n - i + 1][1] = -kInf;
    } else if (s[n - i] == '.') {
      dpSf[n - i + 1][0] = -kInf;
      dpSf[n - i + 1][1] = std::max(dpSf[n - i + 2][0], dpSf[n - i + 2][1]);
    } else {
      dpSf[n - i + 1][0] = dpSf[n - i + 2][1] + 1;
      dpSf[n - i + 1][1] = std::max(dpSf[n - i + 2][0], dpSf[n - i + 2][1]);
    }
  }

  std::vector pf0(n + 2, 0), sf0(n + 2, 0);
  for (int i = 1; i <= n; ++i) {
    pf0[i] = pf0[i - 1] + int(s[i - 1] == 'o');
    sf0[n - i + 1] = sf0[n - i + 2] + int(s[n - i] == 'o');
  }

  auto t = s;
  for (int i = 1; i <= n; ++i) {
    if (s[i - 1] != '?') {
      continue;
    }
    auto can0 = (i == 1 || s[i - 2] != 'o') && (i == n || s[i] != 'o');
    can0 &= pf0[i - 1] + sf0[i + 1] < k && dpPf[i - 1][1] + 1 + dpSf[i + 1][1] >= k;
    auto can1 = std::max(dpPf[i - 1][0], dpPf[i - 1][1]) + std::max(dpSf[i + 1][0], dpSf[i + 1][1]) >= k && pf0[i - 1] + sf0[i + 1] <= k;
    if (can0 && can1) {
      t[i - 1] = '?';
    } else if (can0) {
      t[i - 1] = 'o';
    } else {
      t[i - 1] = '.';
    }
  }
  Println(t);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

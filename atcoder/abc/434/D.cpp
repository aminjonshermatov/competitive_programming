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
  constexpr int kL = 2000;
  std::array<std::array<int, kL>, kL> g{};
  for (int i = 0; i < kL; ++i) {
    g[i].fill(0);
  }

  int n;
  Scan(n);
  std::vector<int> us(n), ds(n), ls(n), rs(n);
  for (int i = 0; i < n; ++i) {
    Scan(us[i], ds[i], ls[i], rs[i]);
    --us[i], --ds[i], --ls[i], --rs[i];

    assert(us[i] <= ds[i]);
    assert(ls[i] <= rs[i]);
    ++g[us[i]][ls[i]];
    if (ds[i] + 1 < kL) {
      --g[ds[i] + 1][ls[i]];
    }
    if (rs[i] + 1 < kL) {
      --g[us[i]][rs[i] + 1];
    }
    if (ds[i] + 1 < kL && rs[i] + 1 < kL) {
      ++g[ds[i] + 1][rs[i] + 1];
    }
  }

  std::array<std::array<int, kL>, kL> pf{};
  for (int i = 0; i < kL; ++i) {
    pf[i].fill(0);
  }
  auto cnt0 = 0;
  for (int i = 0; i < kL; ++i) {
    for (int j = 0; j < kL; ++j) {
      if (i > 0) {
        g[i][j] += g[i - 1][j];
      }
      if (j > 0) {
        g[i][j] += g[i][j - 1];
      }
      if (i > 0 && j > 0) {
        g[i][j] -= g[i - 1][j - 1];
      }
      cnt0 += g[i][j] == 0;
      pf[i][j] += g[i][j] == 1;
      if (i > 0) {
        pf[i][j] += pf[i - 1][j];
      }
      if (j > 0) {
        pf[i][j] += pf[i][j - 1];
      }
      if (i > 0 && j > 0) {
        pf[i][j] -= pf[i - 1][j - 1];
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    auto cur1 = pf[ds[i]][rs[i]];
    if (us[i] > 0) {
      cur1 -= pf[us[i] - 1][rs[i]];
    }
    if (ls[i] > 0) {
      cur1 -= pf[ds[i]][ls[i] - 1];
    }
    if (us[i] > 0 && ls[i] > 0) {
      cur1 += pf[us[i] - 1][ls[i] - 1];
    }
    Print(cnt0 + cur1);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}

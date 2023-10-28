#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  constexpr std::string_view abc{"ABC"};

  int n;
  std::cin >> n;
  std::string r, c;
  std::cin >> r >> c;

  std::vector g(n, std::string(n, '.'));
  auto dfs = [&](auto &f, int i, int j, std::array<int, 5> R, std::array<int, 5> C) -> void {
    if (i == n) {
      bool ok = true;
      for (int ii = 0; ii < n; ++ii) {
        ok &= R[ii] == 7;
      }
      for (int jj = 0; jj < n; ++jj) {
        ok &= C[jj] == 7;
      }
      if (ok) {
        std::cout << "Yes\n";
        for (auto &row : g) {
          std::cout << row << '\n';
        }
        std::exit(0);
      }
      return;
    }
    if (j == n) {
      if (R[i] == 7) {
        f(f, i + 1, 0, R, C);
      }
      return;
    }
    f(f, i, j + 1, R, C);
    for (auto ch : abc) {
      if (R[i] == 0 && r[i] != ch) continue;
      if (C[j] == 0 && c[j] != ch) continue;
      if (R[i] >> (ch - 'A') & 1) continue;
      if (C[j] >> (ch - 'A') & 1) continue;
      g[i][j] = ch;
      R[i] |= 1 << (ch - 'A');
      C[j] |= 1 << (ch - 'A');
      f(f, i, j + 1, R, C);
      C[j] ^= 1 << (ch - 'A');
      R[i] ^= 1 << (ch - 'A');
      g[i][j] = '.';
    }
  };
  dfs(dfs, 0, 0, {0, 0, 0, 0, 0}, {0, 0, 0, 0});
  std::cout << "No\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  solve();
}
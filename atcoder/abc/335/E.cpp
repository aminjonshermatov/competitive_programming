#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;

  std::vector g(n, std::vector<int>(n, -1));

  int lt = 0, rb = n - 1, x = 1;
  for (; lt != rb; ++lt, --rb) {
    for (int k = 0; k < (rb - lt + 1); ++k) {
      g[lt][lt + k] = x++;
    }
    for (int k = 1; k + 1 < (rb - lt + 1); ++k) {
      g[lt + k][rb] = x++;
    }
    for (int k = 0; k < (rb - lt + 1); ++k) {
      g[rb][rb - k] = x++;
    }
    for (int k = 1; k + 1 < (rb - lt + 1); ++k) {
      g[rb - k][lt] = x++;
    }
  }
  for (auto& r : g) {
    for (auto& z : r) {
      if (z == -1) {
        std::cout << "T ";
      } else {
        std::cout << z << ' ';
      }
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;

  auto f = [](int x) -> std::pair<bool, int> {
    int d = -1;
    for (; x > 0;) {
      auto [q, r] = std::div(x, 10);
      if (d != -1 && r != d) {
        return {false, -1};
      }
      d = r;
      x = q;
    }
    return {true, d};
  };

  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    int di;
    std::cin >> di;
    for (int j = 1; j <= di; ++j) {
      auto [fi, xi] = f(i);
      auto [fj, xj] = f(j);
      cnt += fi && fj && xi == xj;
    }
  }
  std::cout << cnt << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
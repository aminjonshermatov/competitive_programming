#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  for (int x = 0; x <= n; ++x) {
    for (int y = 0; x + y <= n; ++y) {
      for (int z = 0; x + y + z <= n; ++z) {
        std::cout << x << ' ' << y << ' ' << z << '\n';
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
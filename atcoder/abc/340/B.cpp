#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int q;
  std::cin >> q;
  std::vector<int> xs;
  while (q-- > 0) {
    int c, x;
    std::cin >> c >> x;
    if (c == 1) {
      xs.emplace_back(x);
    } else {
      std::cout << xs[int(xs.size()) - x] << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
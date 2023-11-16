#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, x;
  std::cin >> n >> x;
  int s = 0;
  for (int i = 0; i < n; ++i) {
    int y;
    std::cin >> y;
    if (y <= x) {
      s += y;
    }
  }
  std::cout << s << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
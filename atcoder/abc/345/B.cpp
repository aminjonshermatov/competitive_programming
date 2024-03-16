#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int64_t x;
  std::cin >> x;
  if (x >= 0) {
    std::cout << (x + 9) / 10 << '\n';
  } else {
    x *= -1;
    std::cout << -(x / 10) << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::vector<int> xs;
  int x;
  for (;;) {
    std::cin >> x;
    xs.emplace_back(x);
    if (x == 0) {
      break;
    }
  }
  std::ranges::reverse(xs);
  for (auto y : xs) {
    std::cout << y << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
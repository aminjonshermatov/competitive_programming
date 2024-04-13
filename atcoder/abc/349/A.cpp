#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  int pos = 0, neg = 0;
  for (int i = 0; i + 1 < n; ++i) {
    int x;
    std::cin >> x;
    (x < 0 ? neg : pos) += x;
  }

  std::cout << -(neg + pos) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
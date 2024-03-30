#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, k;
  std::cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    auto [q, r] = std::div(a, k);
    if (r == 0) {
      std::cout << q << ' ';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
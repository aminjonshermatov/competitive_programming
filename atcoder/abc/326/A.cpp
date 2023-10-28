#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int a, b;
  std::cin >> a >> b;
  bool ok = false;
  ok |= a < b && a + 2 >= b;
  ok |= a > b && a - 3 <= b;
  std::cout << (ok ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  solve();
}
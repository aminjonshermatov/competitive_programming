#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  auto ok = [](int x) -> int {
    return (x / 100) * ((x / 10) % 10) == x % 10;
  };
  while (!ok(n)) ++n;
  std::cout << n << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  solve();
}
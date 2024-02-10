#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int a, b, d;
  std::cin >> a >> b >> d;
  for (auto x = a; ; x += d) {
    std::cout << x << ' ';
    if (x == b) {
      break;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
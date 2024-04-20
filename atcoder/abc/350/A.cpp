#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

void solve() {
  char a, b, c;
  std::cin >> a >> b >> c;
  int x;
  std::cin >> x;
  if (a == 'A' && b == 'B' && c == 'C' && x >= 1 && x <= 349 && x != 316) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
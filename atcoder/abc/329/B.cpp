#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> as(n);
  for (auto &a : as) {
    std::cin >> a;
  }

  sort(as.begin(), as.end());
  as.erase(std::unique(as.begin(), as.end()), as.end());
  std::cout << as[as.size() - 2] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
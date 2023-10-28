#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> as(n);
  for (auto &a : as) {
    std::cin >> a;
  }
  std::sort(as.begin(), as.end());
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    mx = std::max(mx, int(std::lower_bound(as.begin(), as.end(), as[i] + m) - (as.begin() + i)));
  }
  std::cout << mx << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  solve();
}
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, q;
  std::cin >> n >> q;
  std::vector<int> xs(n + 1, 0);
  for (int i = 0; i < q; ++i) {
    int x;
    std::cin >> x;
    xs[x] ^= 1;
  }
  std::cout << n - std::accumulate(xs.begin(), xs.end(), 0) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
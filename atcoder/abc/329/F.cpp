#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, q;
  std::cin >> n >> q;
  std::vector<std::set<int>> cols(n);
  for (int i = 0; i < n; ++i) {
    int c;
    std::cin >> c;
    cols[i].emplace(c);
  }
  while (q-- > 0) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;
    if (cols[a].size() > cols[b].size()) {
      for (auto c : cols[b]) {
        cols[a].emplace(c);
      }
      cols[b] = std::set<int>();
      std::swap(cols[a], cols[b]);
    } else {
      for (auto c : cols[a]) {
        cols[b].emplace(c);
      }
      cols[a] = std::set<int>();
    }
    std::cout << cols[b].size() << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
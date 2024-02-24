#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> ps(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    ps[x - 1] = i + 1;
  }
  int q;
  std::cin >> q;
  while (q-- > 0) {
    int a, b;
    std::cin >> a >> b;
    --a, --b;
    if (ps[a] < ps[b]) {
      std::cout << a + 1 << '\n';
    } else {
      std::cout << b + 1 << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
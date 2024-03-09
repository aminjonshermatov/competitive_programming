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
  for (auto& a : as) {
    std::cin >> a;
  }
  std::map<int, int> prv{}, nxt{};
  prv[as[0]] = -1;
  for (int i = 0; i + 1 < n; ++i) {
    prv[as[i + 1]] = as[i];
    nxt[as[i]] = as[i + 1];
  }
  nxt[as[n - 1]] = -1;
  auto root = as[0];
  int q;
  std::cin >> q;
  while (q-- > 0) {
    char cmd;
    int x;
    std::cin >> cmd >> x;
    if (cmd == '1') {
      int y;
      std::cin >> y;
      // x y z
      auto z = nxt[x];
      nxt[x] = y;
      prv[y] = x;
      nxt[y] = z;
      if (z != -1) {
        prv[z] = y;
      }
    } else {
      // y x z
      auto y = prv[x];
      auto z = nxt[x];
      if (y != -1) {
        nxt[y] = z;
        if (z != -1) {
          prv[z] = y;
        }
      } else {
        root = z;
        prv[z] = -1;
      }
      prv.erase(x);
      nxt.erase(x);
    }
  }
  for (auto cur = root; cur != -1; cur = nxt[cur]) {
    std::cout << cur << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
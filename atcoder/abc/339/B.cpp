#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int h, w, n;
  std::cin >> h >> w >> n;
  std::vector g(h, std::vector<char>(w, '.'));
  auto move = [h, w](int i, int j, int dir) {
    switch (dir) {
      case 0: {
        --i;
        break;
      }
      case 1: {
        ++j;
        break;
      }
      case 2: {
        ++i;
        break;
      }
      case 3: {
        --j;
        break;
      }
      default: assert(false);
    }
    return std::pair((i + h) % h, (j + w) % w);
  };
  for (int i = 0, j = 0, k = 0, dir = 0; k < n; ++k) {
    dir = (dir + (g[i][j] == '.' ? 1 : -1) + 4) % 4;
    g[i][j] ^= '#' ^ '.';
    std::tie(i, j) = move(i, j, dir);
  }
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      std::cout << g[i][j];
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
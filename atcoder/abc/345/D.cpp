#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

constexpr int N = 10;
int h, w, timer = 1, bit[N][N], when[N][N];
inline void upd(int y, int x, int val) {
  for (int i = y; i < h; i = i | (i + 1)) {
    for (int j = x; j < w; j = j | (j + 1)) {
      (when[i][j] == timer ? bit[i][j] : (when[i][j] = timer, bit[i][j] = 0)) += val;
    }
  }
}
inline auto upd(int y1, int x1, int y2, int x2, int val) -> void { // [, r)
  upd(y2, x2, val);
  upd(y1, x1, val);
  upd(y1, x2, -val);
  upd(y2, x1, -val);
}
inline int qry(int y, int x) {
  int ret = 0;
  for (int i = y; i >= 0; i = (i & (i + 1)) - 1) {
    for (int j = x; j >= 0; j = (j & (j + 1)) - 1) {
      ret += when[i][j] == timer ? bit[i][j] : 0;
    }
  }
  return ret;
}
inline void reset() {
  ++timer;
}

void solve() {
  std::memset(bit, 0, sizeof(bit));
  std::memset(when, 0, sizeof(when));

  int n;
  std::cin >> n >> h >> w;
  std::vector<std::pair<int, int>> xs(n);
  for (auto& [a, b] : xs) {
    std::cin >> a >> b;
  }
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  do {
    for (int m2 = 0; m2 < (1 << n); ++m2) {
      for (int x = m2; x > 0;) {
        int i = 31 - __builtin_clz(x);
        std::swap(xs[ord[i]].first, xs[ord[i]].second);
        x ^= 1 << i;
      }

      bool ok = true;
      for (int i = 0, k = 0; i < h && k < n && ok; ++i) {
        for (int j = 0; j < w && k < n && ok; ++j) {
          if (auto z = qry(i, j); z != 0) {
            ok &= z == 1;
            continue;
          }
          ok &= (i + xs[ord[k]].first) <= h && (j + xs[ord[k]].second) <= w;
          upd(i, j, i + xs[ord[k]].first, j + xs[ord[k]].second, 1);
          ++k;
        }
      }
      for (int i = 0; i < h && ok; ++i) {
        for (int j = 0; j < w && ok; ++j) {
          ok &= qry(i, j) == 1;
        }
      }
      if (ok) {
        std::cout << "Yes\n";
        return;
      }
      reset();
      for (int x = m2; x > 0;) {
        int i = 31 - __builtin_clz(x);
        std::swap(xs[ord[i]].first, xs[ord[i]].second);
        x ^= 1 << i;
      }
    }
  } while (std::next_permutation(ord.begin(), ord.end()));
  std::cout << "No\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
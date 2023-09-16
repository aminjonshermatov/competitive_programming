#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int m;
  cin >> m;
  array<string, 3> ss{};
  for (int i = 0; i < 3; ++i) {
    cin >> ss[i];
  }
  int ans = 1e9;
  dbg(m);
  dbg(ss);
  const auto lim = m * 4;
  for (int i = 0; i < lim; ++i) {
    for (int j = 0; j < lim; ++j) {
      for (int k = 0; k < lim; ++k) {
        if (i == j || j == k || k == i) continue;
        if (ss[0][i % m] == ss[1][j % m] && ss[1][j % m] == ss[2][k % m]) {
          ans = min(ans, max({i, j, k}));
        }
      }
    }
  }
  if (ans == 1e9) ans = -1;
  cout << ans << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, q; cin >> n >> q;
  vector<vector<i64>> ft(n + 1, vector<i64>(n + 1, 0));
  auto upd = [&](int x, int y) -> void {
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= n; j += j & -j) {
        ++ft[i][j];
      }
    }
  };
  auto qry = [&](int x, int y) -> i64 {
    i64 ans = 0;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        ans += ft[i][j];
      }
    }
    return ans;
  };

  while (q--) {
    string cmd; cin >> cmd;
    if (cmd.front() == 'A') {
      int x, y; cin >> x >> y;
      upd(x, y);
    } else if (cmd.front() == 'G') {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      tie(x1, x2) = tuple(min(x1, x2), max(x1, x2));
      tie(y1, y2) = tuple(min(y1, y2), max(y1, y2));
      cout << qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1) << '\n';
    } else {
      assert(false);
    }
  }
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

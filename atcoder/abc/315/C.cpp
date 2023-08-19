#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  map<int, vector<i64>> mm;
  for (int i = 0; i < n; ++i) {
    int f, s; cin >> f >> s;
    mm[f].emplace_back(s);
  }
  for (auto &[_, x] : mm) {
    sort(x.rbegin(), x.rend());
  }
  i64 ans = 0, mx = -1;
  for (auto &[_, x] : mm) {
    if (mx == -1) {
      if (x.size() > 1) {
        ans = max(ans, x[0] + x[1] / 2);
      }
      for (auto y : x) {
        mx = max(mx, y);
      }
    } else {
      if (x.size() > 1) {
        ans = max(ans, x[0] + x[1] / 2);
      }
      i64 nmx = -1;
      for (auto y : x) {
        ans = max(ans, y + mx);
        nmx = max(nmx, y);
      }
      mx = max(mx, nmx);
    }
  }
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

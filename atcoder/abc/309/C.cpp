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
  i64 n, k; cin >> n >> k;
  vector<i64> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    cin >> as[i] >> bs[i];
  }

  dbg(as, bs);
  auto can = [&](i64 day) -> bool {
    i64 cur = 0;
    for (int i = 0; i < n; ++i) {
      if (as[i] >= day) {
        cur += bs[i];
      }
    }
    dbg(day, cur);
    return cur <= k;
  };

  i64 lo = 0, hi = 1e10;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    (can(mid) ? hi : lo) = mid;
  }
  cout << hi << '\n';
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

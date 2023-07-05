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
  vector<int> as(n);
  for (auto &a : as) cin >> a;

  vector<int> ids(n);
  iota(ids.begin(), ids.end(), 0);
  sort(ids.begin(), ids.end(), [&](int i, int j) {
    return as[i] < as[j];
  });
  vector<i64> pref(n, 0);
  pref[0] = i64(n - 1) * (n - 2) / 2;
  for (int i = 1; i < n; ++i) {
    pref[i] = pref[i - 1] + i64(n - i - 1) * (n - i - 2) / 2;
  }

  dbg(ids);
  dbg(pref);
  while (q--) {
    i64 k; cin >> k;
    int lo = -1, hi = n - 1;
    while (hi - lo > 1) {
      auto mid = lo + (hi - lo) / 2;
      dbg(lo, hi, mid);
      (pref[mid] >= k ? hi : lo) = mid;
    }
    dbg(k, hi);
    cout << as[ids[hi]] << '\n';
  }
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

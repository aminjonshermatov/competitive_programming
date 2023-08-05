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
  vector<i64> as(n);
  for (auto &a : as) cin >> a;
  sort(as.begin(), as.end());

  vector<i64> pf(n);
  pf[0] = as[0];
  for (int i = 1; i < n; ++i) {
    pf[i] = pf[i - 1] + as[i];
  }
  auto get = [&](int l, int r) -> i64 {
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };

  auto cnt = [&](i64 mid) -> i64 {
    auto i = int(lower_bound(as.begin(), as.end(), mid - 1) - as.begin());
    i64 lo = 0;
    if (i > 0) {
      lo += (mid - 1) * i - get(0, i - 1);
    }
    auto j = int(upper_bound(as.begin(), as.end(), mid) - as.begin());
    i64 hi = 0;
    if (j < n) {
      hi += get(j, n - 1) - mid * (n - j);
    }
    assert(lo >= 0 && hi >= 0);
    return max(lo, hi);
  };

  i64 lo = -1, hi = *max_element(as.begin(), as.end()) + 1;
  while (hi - lo > 2) {
    auto mid = lo + (hi - lo) / 2;
    dbg(lo, hi, mid, cnt(mid), mid+1, cnt(mid+1));
    (cnt(mid) >= cnt(mid + 1) ? lo : hi) = mid + 1;
  }

  dbg(lo, hi);
  i64 ans = numeric_limits<i64>::max();
  for (i64 x = lo - 10; x <= hi + 10; ++x) {
    ans = min(ans, cnt(x));
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

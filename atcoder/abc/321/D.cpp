#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m;
  i64 P;
  cin >> n >> m >> P;
  vector<i64> as(n), bs(m);
  for (auto &a : as) {
    cin >> a;
  }
  for (auto &b : bs) {
    cin >> b;
  }

  sort(as.begin(), as.end());
  sort(bs.begin(), bs.end());
  vector<i64> pf(m);
  for (int i = 0; i < m; ++i) {
    pf[i] = (i > 0 ? pf[i - 1] : 0) + bs[i];
  }
  dbg(as);
  dbg(bs);
  dbg(pf);
  i64 tot = 0;
  for (auto a : as) {
    auto up = int(upper_bound(bs.begin(), bs.end(), P - a) - bs.begin());
    if (up > 0) {
      tot += a * up + pf[up - 1];
    }
    dbg(a, up);
    tot += P * (m - up);
  }
  cout << tot << '\n';
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

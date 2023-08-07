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

  auto bs = as;
  sort(bs.begin(), bs.end());
  for (auto &a : as) {
    a = int(lower_bound(bs.begin(), bs.end(), a) - bs.begin());
  }
  vector<i64> pf(n);
  pf[0] = bs[0];
  for (int i = 1; i < n; ++i) {
    pf[i] = pf[i - 1] + bs[i];
  }

  for (auto a : as) {
    i64 tmp = n;
    auto i = lower_bound(bs.begin(), bs.end(), bs[a]) - bs.begin();
    if (i > 0) {
      tmp += bs[a] * i - pf[i - 1];
    }
    i = upper_bound(bs.begin(), bs.end(), bs[a]) - bs.begin();
    if (i < n) {
      tmp += pf[n - 1] - pf[i - 1] - (n - i) * bs[a];
    }
    cout << tmp << ' ';
  }
  cout << '\n';
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

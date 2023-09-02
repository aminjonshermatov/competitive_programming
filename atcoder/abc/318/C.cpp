#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, d, p;
  cin >> n >> d >> p;
  vector<int> fs(n);
  for (auto &f : fs) {
    cin >> f;
  }

  sort(fs.begin(), fs.end());
  vector<i64> pf(n);
  pf[0] = fs[0];
  for (int i = 1; i < n; ++i) {
    pf[i] = pf[i - 1] + fs[i];
  }
  auto get = [&](int l, int r) -> i64 {
    if (l > r) return 0;
    return pf[r] - (l > 0 ? pf[l - 1] : 0);
  };
  i64 ans = numeric_limits<i64>::max();
  for (int x = 0; x <= n; ++x) {
    i64 c = (x + d - 1) / d;
    ans = min(ans, c * p + get(0, n - 1 - x));
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

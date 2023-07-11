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
  int n; cin >> n;
  vector<i64> as(n);
  for (auto &a : as) cin >> a;

  if (n < 3) {
    cout << *max_element(as.begin(), as.end()) << '\n';
    return;
  }

  int l = 0;
  while (l < n && as[l] <= 0) ++l;
  int r = n - 1;
  while (r >= 0 && as[r] <= 0) --r;
  if (l > r) {
    cout << *min_element(as.begin(), as.end()) << '\n';
    return;
  }
  i64 a = 0;
  for (int i = l; i <= r; i += 2) {
    a += as[i];
  }
  i64 b = 0;
  for (int i = l + 1; i <= r; i += 2) {
    b += as[i];
  }
  cout << max(a, b) << '\n';
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

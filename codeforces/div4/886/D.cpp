#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> as(n);
  for (auto &a : as) cin >> a;

  sort(as.begin(), as.end());
  int ans = n - 1, cur = 1;
  for (int i = 1; i < n; ++i) {
    if (as[i] - as[i - 1] > k) {
      ans = min(ans, n - cur);
      cur = 1;
    } else {
      ++cur;
    }
  }
  cout << min(ans, n - cur) << '\n';
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

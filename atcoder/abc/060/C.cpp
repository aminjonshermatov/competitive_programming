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
  i64 n, t; cin >> n >> t;
  vector<pair<int, int>> intervals;
  intervals.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    intervals.emplace_back(x, x + t);
  }
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    int start = intervals[i].first;
    int end = intervals[i].second;
    while (i + 1 < n && intervals[i + 1].first <= end) {
      end = max(end, intervals[++i].second);
    }
    ans += end - start;
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

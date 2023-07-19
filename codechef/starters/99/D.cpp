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

  vector<int> as(n), bs(n);
  vector<pair<int, int>> by_val(2 * n);
  for (int i = 0; i < n; ++i) {
    cin >> as[i] >> bs[i];
    if (as[i] > bs[i]) swap(as[i], bs[i]);
    by_val[i].first = as[i];
    by_val[n + i].first = bs[i];
    by_val[i].second = by_val[n + i].second = i;
  }

  sort(by_val.begin(), by_val.end());
  multiset<int> lhs;
  {
    vector<bool> used(n, false);
    for (int i = 2 * n - 1; i >= 0; --i) {
      if (used[by_val[i].second]) continue;
      used[by_val[i].second] = true;
      lhs.emplace(by_val[i].first);
    }
  }
  int ans = 1e9 + 10;
  vector<bool> used(n, false);
  for (int i = 2 * n - 1; i > 0; --i) {
    auto [v, id] = by_val[i];
    lhs.erase(lhs.find(v));
    dbg(v, lhs);
    ans = min(ans, v - *lhs.rbegin());
    if (used[id]) {
      break;
    } else {
      lhs.emplace(as[id]);
    }
    used[id] = true;
  }
  cerr << '\n';
  cout << ans << '\n';
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

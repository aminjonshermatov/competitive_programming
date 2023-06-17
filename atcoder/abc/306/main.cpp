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
  int n, m; cin >> n >> m;
  vector<vector<int>> g(n, vector<int>(m));
  vector<int> nums;
  nums.reserve(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> g[i][j];
      nums.emplace_back(g[i][j]);
    }
    sort(g[i].begin(), g[i].end());
  }
  sort(nums.begin(), nums.end());
  nums.resize(unique(nums.begin(), nums.end()) - nums.begin());
  assert(nums.size() == n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      g[i][j] = int(lower_bound(nums.begin(), nums.end(), g[i][j]) - nums.begin());
    }
  }
  dbg(g);
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int i2 = i + 1; i2 < n; ++i2) {
        dbg(i, j, i2, int(upper_bound(g[i2].begin(), g[i2].end(), g[i][j]) - g[i2].begin()));
        ans += j + 1 + int(upper_bound(g[i2].begin(), g[i2].end(), g[i][j]) - g[i2].begin());
      }
    }
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

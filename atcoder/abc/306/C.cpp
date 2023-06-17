#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> nums(n + 1);
  for (int i = 0; i < 3 * n; ++i) {
    int x; cin >> x;
    nums[x].emplace_back(i);
  }
  vector<int> ans(n);
  iota(ans.begin(), ans.end(), 1);
  std::sort(ans.begin(), ans.end(), [&](int i, int j) {
    return nums[i][1] < nums[j][1];
  });
  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << '\n';
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

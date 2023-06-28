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
  vector<int> fr(n + 1, 0);
  multiset<pair<int, int>> nums;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ++fr[x];
    nums.emplace(x, i);
  }

  vector<int> ans;
  int left = n;

  while (left > 0) {
    int i = 0, dec = 0;
    for (; i <= n; ++i) {
      if (fr[i] == 0) break;
      ++dec;
      --fr[i];
      nums.erase(nums.lower_bound(pair(i, 0)));
    }
    if (dec == 0) {
      dec = 1;
      i = 0;
      assert(!nums.empty());
      nums.erase(nums.begin());
    }
    ans.emplace_back(i);
    left -= dec;
  }
  cout << ans.size() << '\n';
  for (auto x : ans) {
    cout << x << ' ';
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

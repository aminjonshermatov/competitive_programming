#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 =  int64_t;
using u64 = uint64_t;

void solve() {
  int n; cin >> n;
  vector<int> cnt(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    if (a <= n) {
      ++cnt[a];
    }
  }
  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      dp[j] += cnt[i];
    }
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n';
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

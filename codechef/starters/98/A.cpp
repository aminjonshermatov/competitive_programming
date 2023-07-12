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
  map<int, int> cnt{};
  for (int j = 0; j < 2; ++j) {
    for (int i = 0; i < n; ++i) {
      int x; cin >> x;
      ++cnt[x];
    }
  }
  int ans = 0;
  for (auto [_, x] : cnt) {
    ans = max(ans, x);
  }
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> as(n);
  for (auto &a : as) {
    a = 0;
    for (int i = 0; i < k; ++i) {
      char x; cin >> x;
      a = a * 2 + x - '0';
    }
  }
  int ans = 1e9;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      ans = min(ans, __builtin_popcount(as[i] ^ as[j]));
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

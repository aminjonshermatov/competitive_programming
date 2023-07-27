#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<pair<int, int>> as(n);
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    if (x > k) {
      x %= k;
      if (x == 0) x += k;
    }
    as[i] = {x, -i};
  }
  sort(as.rbegin(), as.rend());
  for (auto [_, i] : as) {
    cout << -i + 1 << ' ';
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
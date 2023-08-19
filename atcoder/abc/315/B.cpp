#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int m; cin >> m;
  vector<int> ds(m);
  for (auto &d : ds) cin >> d;

  auto mid = (accumulate(ds.begin(), ds.end(), 0) + 1) / 2;
  int cur = 0;
  for (int i = 0; i < m; ++i) {
    if (cur + ds[i] >= mid) {
      dbg(cur, mid);
      cout << i + 1 << ' ' << mid - cur << '\n';
      return;
    } else {
      cur += ds[i];
    }
  }
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

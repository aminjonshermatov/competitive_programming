#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) cin >> a;

  sort(as.begin(), as.end());
  for (int i = 1; i < n; ++i) {
    if (as[i - 1] + 1 != as[i]) {
      cout << as[i - 1] + 1 << '\n';
      return;
    }
  }
  cout << as.back() + 1 << '\n';
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

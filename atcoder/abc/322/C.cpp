#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> as(m);
  for (auto &a : as) {
    cin >> a;
  }
  for (int i = 1; i <= n; ++i) {
    cout << *lower_bound(as.begin(), as.end(), i) - i << ' ';
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

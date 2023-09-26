#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> as(n);
  bool ok = false;
  for (auto &a : as) {
    cin >> a;
    ok |= a == k;
  }
  cout << (ok ? "Yes" : "No") << '\n';
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

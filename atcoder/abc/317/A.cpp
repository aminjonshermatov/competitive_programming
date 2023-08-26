#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, h, x;
  cin >> n >> h >> x;

  vector<int> ps(n);
  for (auto &p : ps) cin >> p;

  for (int i = 0; i < n; ++i) {
    if ((h + ps[i]) >= x) {
      cout << i + 1 << '\n';
      return;
    }
  }
  assert(false);
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

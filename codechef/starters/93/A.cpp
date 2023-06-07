#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  for (int a = 0; a <= 200; ++a) {
    for (int b = 0; b <= 200; ++b) {
      if ((n - a + 3 * b) == (m + a - b)) {
        cout << "YES\n";
        return;
      }
    }
  }
  cout << "NO\n";
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

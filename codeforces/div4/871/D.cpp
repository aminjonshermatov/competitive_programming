// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

bool ok(int n, int m) {
  if (n < m) return false;
  if (n == m) return true;
  auto [q, r] = div(n, 3);
  if (r != 0) return false;
  return ok(2 * q, m) || ok(q, m);
}

void solve() {
  int n, m; cin >> n >> m;
  cout << (ok(n, m) ? "YES" : "NO") << '\n';
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

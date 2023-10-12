#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;
  vector<string> g(n);
  for (auto &r : g) {
     cin >> r;
  }
  int ans = 0;
  for (int lev = 0; lev < n / 2; ++lev) {
    string a;
    for (int j = lev; j < n - lev - 1; ++j) {
      a.push_back(g[lev][j]);
    }
    string b;
    for (int i = lev; i < n - lev - 1; ++i) {
      b.push_back(g[i][n - lev - 1]);
    }
    string c;
    for (int j = n - lev - 1; j > lev; --j) {
      c.push_back(g[n - lev - 1][j]);
    }
    string d;
    for (int i = n - lev - 1; i > lev; --i) {
      d.push_back(g[i][lev]);
    }
    for (int i = 0; i < a.size(); ++i) {
      auto mx = max({a[i], b[i], c[i], d[i]});
      ans += mx - a[i];
      ans += mx - b[i];
      ans += mx - c[i];
      ans += mx - d[i];
    }
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

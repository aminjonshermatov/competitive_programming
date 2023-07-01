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
  vector<string> cs(n);
  for (auto &c : cs) cin >> c;
  vector<string> ds(m);
  for (int i = 0; i < m; ++i) {
    cin >> ds[i];
  }
  int p0; cin >> p0;
  map<string, int> ps;
  for (int i = 0; i < m; ++i) {
    int p; cin >> p;
    ps[ds[i]] = p;
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (ps.count(cs[i]) > 0) {
      ans += ps[cs[i]];
    } else {
      ans += p0;
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

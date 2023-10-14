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
  string s;
  cin >> n >> s;
  const auto nn = int(s.size());
  vector<i64> pf(n, 0), sf(n, 0);
  for (int i = 0; i < n; ++i) {
    string t;
    cin >> t;
    {
      int ii = 0;
      for (auto c : t) {
        ii += ii < nn && s[ii] == c;
      }
      pf[i] = ii;
    }
    {
      int ii = nn - 1;
      reverse(t.begin(), t.end());
      for (auto c : t) {
        ii -= ii >= 0 && s[ii] == c;
      }
      sf[i] = nn - ii - 1;
    }
  }
  dbg(pf);
  dbg(sf);
  sort(sf.begin(), sf.end());
  i64 cnt = 0;
  for (auto p : pf) {
    cnt += int(sf.end() - lower_bound(sf.begin(), sf.end(), nn - p));
  }
  cout << cnt << '\n';
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s, t;
  cin >> s >> t;

  const auto n = int(s.size());
  const auto m = int(t.size());

  vector<int> dp(m + 1, 0);
  vector prv(n + 1, vector<char>(m + 1, 'x'));
  for (int i = 1; i <= n; ++i) {
    vector<int> ndp(m + 1, 0);
    for (int j = 1; j <= m; ++j) {
      if (s[i - 1] == t[j - 1] && dp[j - 1] + 1 > ndp[j]) {
        ndp[j] = dp[j - 1] + 1;
        prv[i][j] = 'd';
      }
      if (dp[j] > ndp[j]) {
        ndp[j] = dp[j];
        prv[i][j] = 'u';
      }
      if (ndp[j - 1] > ndp[j]) {
        ndp[j] = ndp[j - 1];
        prv[i][j] = 'l';
      }
    }
    dp.swap(ndp);
  }
  auto cur = pair(n, m);
  for (int j = 0; j <= m; ++j) {
    if (dp[j] > dp[cur.second]) {
      cur.second = j;
    }
  }

  string res;
  res.reserve(n);
  while (cur.first >= 0 && cur.second >= 0) {
    switch (prv[cur.first][cur.second]) {
      case 'd':
        res.push_back(s[cur.first - 1]);
        --cur.first, --cur.second;
        break;
      case 'u':
        --cur.first;
        break;
      case 'l':
        --cur.second;
        break;
      case 'x':
        goto done;
      default:
        assert(false);
    }
  }
  done:
  reverse(res.begin(), res.end());
  cout << res << '\n';
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

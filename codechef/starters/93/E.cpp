#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;

  vector<pair<char, int>> S;
  for (auto ch : s) {
    if (!S.empty() && ch == S.back().first) ++S.back().second;
    else S.emplace_back(ch, 1);
  }
  dbg(S);
  const int m = static_cast<int>(S.size());
  vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
  vector<vector<int>> prv_bal(m + 1, vector<int>(n + 1, -1));
  dp[0][0] = true;
  for (int i = 0; i < m; ++i) {
    auto [ch, len] = S[i];
    for (int bal = 0; bal <= n; ++bal) {
      if (!dp[i][bal]) continue;
      if (bal + len <= n) {
        dp[i + 1][bal + len] = dp[i][bal];
        prv_bal[i + 1][bal + len] = bal;
      }
      if (bal - len >= 0) {
        dp[i + 1][bal - len] = dp[i][bal];
        prv_bal[i + 1][bal - len] = bal;
      }
    }
  }

  if (!dp[m][0]) {
    cout << "NO\n";
    return;
  }
  string ans;
  int idx = m, bal = 0;
  while (idx > 0) {
    if (prv_bal[idx][bal] > bal) {
      ans.append(S[idx - 1].second, ')');
    } else {
      ans.append(S[idx - 1].second, '(');
    }
    bal = prv_bal[idx--][bal];
  }
  reverse(ans.begin(), ans.end());
  cout << "YES\n" << ans << '\n';
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

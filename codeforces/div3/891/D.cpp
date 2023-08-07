#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> as(n), bs(n);
  for (auto &a : as) cin >> a;
  for (auto &b : bs) cin >> b;

  vector<pair<int, int>> cs(n);
  for (int i = 0; i < n; ++i) {
    cs[i] = pair(as[i] - bs[i], i);
  }
  sort(cs.rbegin(), cs.rend());
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (cs[i].first == cs[0].first) {
      ans.emplace_back(cs[i].second);
    }
  }
  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (auto i : ans) {
    cout << i + 1 << ' ';
  }
  cout << '\n';
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

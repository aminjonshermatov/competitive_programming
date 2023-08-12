#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> cs(n);
  for (auto &c : cs) {
    int x; cin >> x;
    c.resize(x);
    for (auto &y : c) {
      cin >> y;
    }
  }
  int x; cin >> x;
  vector<pair<int, int>> pos;
  for (int i = 0; i < n; ++i) {
    if (count(cs[i].begin(), cs[i].end(), x) > 0) {
      pos.emplace_back(cs[i].size(), i);
    }
  }
  sort(pos.begin(), pos.end());
  vector<int> ans;
  for (int i = 0; i < pos.size(); ++i) {
    if (pos[i].first == pos[0].first) {
      ans.emplace_back(pos[i].second + 1);
    } else {
      break;
    }
  }
  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (auto i : ans) {
    cout << i << ' ';
  }
  cout << '\n';
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

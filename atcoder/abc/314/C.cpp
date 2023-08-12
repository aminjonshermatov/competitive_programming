#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  string s; cin >> s;
  vector<vector<int>> ids(m);
  vector<int> cs(n);
  for (int i = 0; i < n; ++i) {
    cin >> cs[i];
    ids[--cs[i]].emplace_back(i);
  }
  dbg(ids);
  vector<int> ptr(m), chs(n);
  for (int i = 0; i < m; ++i) {
    ptr[i] = int(ids[i].size()) - 1;
  }
  for (int i = 0; i < n; ++i) {
    chs[i] = ids[cs[i]][ptr[cs[i]]];
    ptr[cs[i]] = (ptr[cs[i]] + 1) % ids[cs[i]].size();
  }
  dbg(chs);
  for (int i = 0; i < n; ++i) {
    cout << s[chs[i]];
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

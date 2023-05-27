#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m, h, k; cin >> n >> m >> h >> k;
  string moves; cin >> moves;
  set<pair<int, int>> items;
  for (int i = 0; i < m; ++i) {
    int x, y; cin >> x >> y;
    items.emplace(x, y);
  }
  pair<int, int> cur{0, 0};
  for (int i = 0; i < n; ++i) {
    if (--h < 0) {
      cout << "No";
      return;
    }
    switch (moves[i]) {
      case 'R':
        ++cur.first;
        break;
      case 'L':
        --cur.first;
        break;
      case 'U':
        ++cur.second;
        break;
      case 'D':
        --cur.second;
        break;
    }
    if (items.count(cur) > 0 && h < k) {
      h = k;
      items.erase(cur);
    }
  }
  assert(h >= 0);
  cout << "Yes";
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

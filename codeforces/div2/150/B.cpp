#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int q; cin >> q;
  vector<int> cur;
  string ans(q, '0');
  bool seen = false;
  for (int i = 0; i < q; ++i) {
    int x; cin >> x;
    if (cur.size() > 1 && ((seen && (x < cur.back() || x > cur.front())) || (!seen && x > cur.front() && x < cur.back()))) {
      ans[i] = '0';
    } else {
      ans[i] = '1';
      seen |= !cur.empty() && x < cur.back();
      cur.push_back(x);
    }
    dbg(cur, seen);
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

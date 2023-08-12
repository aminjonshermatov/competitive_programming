#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  int q; cin >> q;
  set<int> upd;
  int state = -1;
  while (q--) {
    int t, x;
    char c;
    cin >> t >> x >> c;
    --x;
    if (t == 1) {
      upd.emplace(x);
      s[x] = c;
    } else if (t == 2) {
      upd.clear();
      state = 0; // lo
    } else if (t == 3) {
      upd.clear();
      state = 1; // up
    } else {
      assert(false);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (upd.count(i) > 0) {
      continue;
    }
    if (state == 0) {
      s[i] = tolower(s[i]);
    } else if (state == 1) {
      s[i] = toupper(s[i]);
    }
  }
  cout << s << '\n';
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

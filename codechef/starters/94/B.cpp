#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, b; cin >> n >> b;
  vector<int> pos;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    bool _all = true;
    for (int ib = 30; ib >= 0; --ib) {
      if (b >> ib & 1) {
        _all &= x >> ib & 1;
      }
    }
    if (_all) {
      pos.emplace_back(x);
    }
  }
  if (pos.empty()) {
    cout << "NO\n";
    return;
  }
  auto x = pos.front();
  for (int i = 1; i < pos.size(); ++i) {
    x &= pos[i];
  }
  cout << (x == b ? "Yes" : "No") << '\n';
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

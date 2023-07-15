#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> ps(n), cs(n);
  vector<map<int, int>> fs(n);
  for (int i = 0; i < n; ++i) {
    cin >> ps[i] >> cs[i];
    for (int j = 0; j < cs[i]; ++j) {
      int x; cin >> x;
      ++fs[i][x];
    }
  }

  bool ok = false;
  for (int i = 0; i < n && !ok; ++i) {
    for (int j = 0; j < n && !ok; ++j) {
      if (i == j) continue;
      bool loc = ps[i] >= ps[j];
      for (auto [fi, cnt] : fs[i]) {
        loc &= fs[j].count(fi) > 0 && fs[j][fi] >= cnt;
      }
      if (ps[i] == ps[j]) {
        bool found = false;
        for (auto [fj, cnt] : fs[j]) {
          found |= fs[i].count(fj) == 0;
        }
        loc &= found;
      }
      ok |= loc;
    }
  }
  cout << (ok ? "Yes" : "No") << '\n';
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

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
  map<int, int> cntA, cntB;
  {
    int prv, cnt = 1;
    cin >> prv;
    for (int i = 1; i < n; ++i) {
      int x; cin >> x;
      if (x != prv) {
        cntA[prv] = max(cntA[prv], cnt);
        cnt = 0;
      }
      ++cnt;
      prv = x;
    }
    cntA[prv] = max(cntA[prv], cnt);
  }
  {
    int prv, cnt = 1;
    cin >> prv;
    for (int i = 1; i < n; ++i) {
      int x; cin >> x;
      if (x != prv) {
        cntB[prv] = max(cntB[prv], cnt);
        cnt = 0;
      }
      ++cnt;
      prv = x;
    }
    cntB[prv] = max(cntB[prv], cnt);
  }
  int ans = 0;
  for (auto [k, v] : cntA) {
    ans = max(ans, v + cntB[k]);
  }
  for (auto [k, v] : cntB) {
    ans = max(ans, v + cntA[k]);
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

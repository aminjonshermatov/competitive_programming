#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int q; cin >> q;
  vector<pair<i64, set<i64>>> pf(q + 1);
  vector<int> par(q + 1);
  par[1] = -1;
  pf[1].first = 1;
  pf[1].second.emplace(1);
  int sz = 1;
  for (int i = 0; i < q; ++i) {
    char cmd; cin >> cmd;
    if (cmd == '+') {
      int v, x; cin >> v >> x;
      ++sz;
      pf[sz].first = pf[v].first;
      pf[sz].second = pf[v].second;
      pf[sz].second.emplace(pf[v].first += x);
      par[sz] = v;
    } else if (cmd == '?') {
      int u, v, k; cin >> u >> v >> k;
      if (u == v || pf[v].first == k) {
        cout << "Yes\n";
        continue;
      }
      assert(u == 1);
      bool ok = false;
      while (!ok && v != -1) {
        if (~par[v]) {
          ok |= pf[par[v]].second.count(k - pf[v].first) > 0;
        }
        v = par[v];
      }
      cout << (ok ? "Yes" : "No") << '\n';
    }
  }
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

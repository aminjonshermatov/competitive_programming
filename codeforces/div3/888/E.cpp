#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

constexpr auto inf = numeric_limits<i64>::max();

void solve() {
  int n, k; cin >> n >> k;
  vector<i64> cs(n);
  for (auto &c : cs) cin >> c;

  vector<int> unlim(k);
  for (auto &x : unlim) {
    cin >> x;
    --x;
  }

  vector<vector<int>> g(n), ig(n);
  vector<int> deg(n, 0);
  for (int i = 0; i < n; ++i) {
    int m; cin >> m;
    for (int j = 0; j < m; ++j) {
      int x; cin >> x;
      --x;
      g[x].emplace_back(i);
      ig[i].emplace_back(x);
      ++deg[i];
    }
  }

  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 0) {
      q.emplace(i);
    }
  }
  vector<int> ord;
  ord.reserve(n);
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    ord.emplace_back(v);
    for (auto u : g[v]) {
      if (--deg[u] == 0) {
        q.emplace(u);
      }
    }
  }

  vector<i64> mn(n, inf);
  for (auto v : unlim) {
    mn[v] = 0;
  }
  dbg(mn, ord);
  for (auto v : ord) {
    if (!ig[v].empty()) {
      i64 sm = 0;
      for (auto u : ig[v]) {
        sm += min(cs[u], mn[u]);
      }
      mn[v] = min(mn[v], sm);
    }
    mn[v] = min(mn[v], cs[v]);
  }
  for (auto x : mn) {
    cout << x << ' ';
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

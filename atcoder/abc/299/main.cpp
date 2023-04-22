// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  int k; cin >> k;
  vector<pair<int, int>> pd(k);
  for (auto &[p, d] : pd) cin >> p >> d, --p;

  if (k == 0) {
    cout << "Yes\n" << string(n, '1') << '\n';
    return ;
  }

  sort(pd.begin(), pd.end(), [](const auto &lhs, const auto &rhs) {
    return lhs.second >= rhs.second;
  });

  vector<int> freq(n, 0);
  for (int i = 0; i < k; ++i) {
    auto [p, d] = pd[i];
    queue<int> q;
    vector<bool> used(n, false);
    q.emplace(p);
    used[p] = true;
    while (!q.empty() && d >= 0) {
      for (int sz(q.size()); sz--;) {
        auto v = q.front(); q.pop();
        if (d == 0) {
          ++freq[v];
        } else if (freq[v] > 0) {
          if (freq[v] == 1) {
            cout << "No\n";
            return ;
          }
          --freq[v];
        }
        else {
          for (auto u : g[v]) {
            if (used[u]) continue;
            used[u] = true;
            q.emplace(u);
          }
        }
      }
      --d;
    }
  }

  if (none_of(freq.begin(), freq.end(), [](auto x) { return x > 0; })) {
    cout << "No\n";
    return ;
  }

  cout << "Yes\n";
  for (int v = 0; v < n; ++v) {
    cout << (freq[v] > 0);
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

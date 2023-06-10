#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr auto inf = numeric_limits<int>::max();

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
  int n, m; cin >> n >> m;
  vector<set<int>> g(n);

  vector<int> pr(n), dist(n);
  auto bfs = [&]() {
    queue<int> q;
    q.emplace(n - 1);
    fill(pr.begin(), pr.end(), -1);
    fill(dist.begin(), dist.end(), inf);
    dist[n - 1] = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop();
      for (auto u : g[v]) {
        if (dist[v] + 1 < dist[u]) {
          dist[u] = dist[v] + 1;
          pr[u] = v;
          q.emplace(u);
        }
      }
    }
  };

  bool ans_found = false;
  int cur = 0, cur_d = 0;
  vector<int> path;
  while (true) {
    int k; cin >> k;
    ++cur_d;
    vector<int> adj;
    adj.reserve(k);
    bool _last = false;
    for (int i = 0; i < k; ++i) {
      int u; cin >> u;
      --u;
      g[cur].emplace(u);
      g[u].emplace(cur);
      adj.emplace_back(u);
      _last |= u == n - 1;
    }
    if (_last) {
      cout << n << endl;
      return;
    }

    if (!ans_found) {
      bfs();
      for (auto v : adj) {
        if (dist[v] != inf && dist[v] + cur_d <= 2 * n) {
          path.clear();

          goto found;
        }
      }
      auto r_idx = (abs(int(rnd())) % k + k) % k;
      assert(clamp(r_idx, 0, k - 1) == r_idx);
      cur = adj[r_idx];
    } else {
      found:
      assert(!path.empty());
      cur = path.back();
      path.pop_back();
    }
    cout << cur + 1 << endl;
    if (cur + 1 == n || (ans_found && path.empty())) break;
  }
}

bool is_multi = false;

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(nullptr);
  // cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

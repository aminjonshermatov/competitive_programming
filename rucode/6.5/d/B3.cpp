#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr auto inf = numeric_limits<int>::max();

constexpr array<int, 5> dk{1, 0, -1, 0, 1};

void solve() {
  int n, m; cin >> m >> n;
  vector<vector<char>> g(n, vector<char>(m));
  pair<int, int> any_s{-1,-1};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> g[i][j];
      if (any_s.first == -1 && g[i][j] == '.') {
        any_s = pair(i, j);
      }
    }
  }

  auto ok = [&n, &m](int i, int j) -> bool {
    return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j;
  };
  auto get_max_coor = [&](vector<vector<int>> &dist) -> pair<int, int> {
    pair<int, int> ans{-1, -1};
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (dist[i][j] == inf) continue;
        if (ans.first == -1 || dist[ans.first][ans.second] < dist[i][j]) {
          ans = pair(i, j);
        }
      }
    }
    assert(ans.first != -1);
    return ans;
  };
  auto bfs = [&](pair<int, int> initial) -> vector<vector<int>> {
    vector<vector<int>> dist(n, vector<int>(m, inf));
    queue<pair<int, int>> q;
    dist[initial.first][initial.second] = 0;
    q.emplace(initial);
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop();
      for (int k = 0; k < 4; ++k) {
        auto ni = i + dk[k];
        auto nj = j + dk[k + 1];
        if (!ok(ni, nj) || g[ni][nj] != '.' || dist[ni][nj] != inf) {
          continue;
        }
        dist[ni][nj] = dist[i][j] + 1;
        q.emplace(ni, nj);
      }
    }
    return dist;
  };

  auto d1 = bfs(any_s);
  auto d2 = bfs(get_max_coor(d1));
  auto d3 = bfs(get_max_coor(d2));
  auto [i, j] = get_max_coor(d3);
  cout << d3[i][j] << '\n';
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

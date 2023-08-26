#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m;
  cin >> n >> m;

  vector<string> g(n);
  pair<int, int> S{}, G{};
  vector<pair<int, int>> hor, ver;
  for (int i = 0; i < n; ++i) {
    cin >> g[i];
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '>' || g[i][j] == '<') {
        hor.emplace_back(i, j);
      } else if (g[i][j] == '^' || g[i][j] == 'v') {
        ver.emplace_back(i, j);
      } else if (g[i][j] == 'S') {
        S = pair(i, j);
      } else if (g[i][j] == 'G') {
        G = pair(i, j);
      }
    }
  }

  auto ok = [&](int i, int j) -> bool {
    return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j;
  };
  auto can_move = [&](int i, int j) -> bool {
    assert(ok(i, j));
    return g[i][j] != '#' && g[i][j] != '>' && g[i][j] != '<' && g[i][j] != '^' && g[i][j] != 'v';
  };

  for (auto [i, j] : hor) {
    int dj = g[i][j] == '>' ? 1 : -1;
    for (j += dj; ok(i, j) && can_move(i, j) && g[i][j] != '+'; j += dj) {
      g[i][j] = '+';
    }
  }
  for (auto [i, j] : ver) {
    int di = g[i][j] == 'v' ? 1 : -1;
    for (i += di; ok(i, j) && can_move(i, j) && g[i][j] != '-'; i += di) {
      g[i][j] = '-';
    }
  }

  constexpr array<int, 5> dk{1, 0, -1, 0, 1};

  vector<vector<int>> dist(n, vector<int>(m, -1));
  queue<pair<int, int>> q;
  dist[S.first][S.second] = 0;
  q.emplace(S.first, S.second);
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (int k = 0; k < 4; ++k) {
      auto ni = i + dk[k];
      auto nj = j + dk[k + 1];
      if (!ok(ni, nj) || !(g[ni][nj] == '.' || g[ni][nj] == 'G') || dist[ni][nj] != -1) continue;
      dist[ni][nj] = dist[i][j] + 1;
      q.emplace(ni, nj);
    }
  }
  cout << dist[G.first][G.second] << '\n';
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

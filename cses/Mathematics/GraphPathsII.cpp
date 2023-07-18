#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;
constexpr auto inf = numeric_limits<i64>::max();

struct Matrix : vector<vector<i64>> {
  Matrix(int n, int m, i64 def) : vector<vector<i64>>(n, vector<i64>(m, def)) { }
};

Matrix& operator*=(Matrix &self, const Matrix &other) {
  assert(self.size() == other.front().size());
  const int n(self.size());
  Matrix res(n, n, inf);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        if (self[i][k] == inf || other[k][j] == inf) continue;
        res[i][j] = min(res[i][j], self[i][k] + other[k][j]);
      }
    }
  }
  return self = res;
}

Matrix power(Matrix mat, i64 b) {
  Matrix res(mat.size(), mat.size(), 0);

  bool assigned = false;
  for (; b > 0; b >>= 1, mat *= mat) {
    if (b & 1) {
      if (assigned) {
        res *= mat;
      } else {
        res = mat;
        assigned = true;
      }
    }
  }
  return res;
}

void solve() {
  int n, m, k; cin >> n >> m >> k;
  Matrix adj(n, n, inf);
  for (int i = 0; i < m; ++i) {
    int u, v;
    i64 w;
    cin >> u >> v >> w;
    --u, --v;
    adj[u][v] = min(adj[u][v], w);
  }

  dbg(adj);
  auto ans = power(adj, k)[0][n - 1];
  cout << (ans == inf ? -1 : ans) << '\n';
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

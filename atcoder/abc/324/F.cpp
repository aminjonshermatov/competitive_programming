#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;
using ld = long double;

struct Edge {
    int u, v;
    i64 b, c;
    bool operator<(const Edge &other) const {
      return pair(u, v) < pair(other.u, other.v);
    }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<Edge> es(m);
  for (auto &[u, v, b, c] : es) {
    int64_t bb, cc;
    cin >> u >> v >> bb >> cc;
    b = bb;
    c = cc;
    --u, --v;
  }

  sort(es.begin(), es.end());

  ld lo = 0, hi = 2e9 + 10;
  constexpr auto ninf = numeric_limits<int>::min();
  for (int _ = 0; _ < 120; ++_) {
    ld mid = lo + (hi - lo) / 2;
    vector<ld> dp(n, ninf);
    dp[0] = 0;
    for (auto &e : es) {
      dp[e.v] = max(dp[e.v], dp[e.u] + e.b - e.c * mid);
    }
    (dp[n - 1] >= 0 ? lo : hi) = mid;
  }
  cout << fixed << setprecision(12) << lo << '\n';
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

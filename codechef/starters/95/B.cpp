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
  int n, m, h; cin >> n >> m >> h;
  vector<i64> cs(n), ps(m);
  for (auto &c : cs) cin >> c;
  for (auto &p : ps) cin >> p;
  sort(cs.rbegin(), cs.rend());
  sort(ps.rbegin(), ps.rend());

  auto can = [&](i64 E) -> bool {
    i64 sm = 0;
    for (int i = 0; i < min(n, m); ++i) {
      sm += min(cs[i], ps[i] * h);
    }
    return sm >= E;
  };

  i64 lo = 0, hi = 1e12;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    (can(mid) ? lo : hi) = mid;
  }
  cout << lo << '\n';
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

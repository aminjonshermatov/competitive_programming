#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  i64 n, w; cin >> n >> w;
  vector<i64> as(n);
  for (auto &a : as) cin >> a;

  auto n_lhs = n / 2;
  auto n_rhs = n - n_lhs;
  unordered_map<i64, int> sums_l;
  for (int mask = 0; mask < (1 << n_lhs); ++mask) {
    i64 sm = 0;
    for (int i = 0; i < n_lhs && sm <= w; ++i) {
      if (mask >> i & 1) {
        sm += as[i];
      }
    }
    if (sm > w) continue;
    ++sums_l[sm];
  }
  i64 cnt = 0;
  for (int mask = 0; mask < (1 << n_rhs); ++mask) {
    i64 sm = 0;
    for (int i = 0; i < n_rhs && sm <= w; ++i) {
      if (mask >> i & 1) {
        sm += as[n_lhs + i];
      }
    }
    if (sm > w) continue;
    auto it = sums_l.find(w - sm);
    if (it == sums_l.end()) continue;
    cnt += it->second;
  }

  cout << cnt << '\n';
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

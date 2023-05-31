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
  i64 n, k; cin >> n >> k;
  vector<i64> A(n);
  for (auto &a : A) cin >> a;

  auto can = [&](i64 gc) -> bool {
    i64 sm = 0;
    for (auto a : A) {
      sm += min(gc, a);
    }
    return sm >= gc * k;
  };

  i64 lo = 0, hi = accumulate(A.begin(), A.end(), i64(0)) + 1;
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

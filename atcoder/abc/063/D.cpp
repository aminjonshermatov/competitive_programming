#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int64_t n, a, b; cin >> n >> a >> b;
  vector<int64_t> H(n);
  for (auto &h : H) cin >> h;

  auto can = [&](int64_t turn) -> bool {
    int64_t cnt = 0;
    for (auto h : H) {
      auto left = h - b * turn;
      if (left <= 0) continue;
      // a * x + (turn - x) * b >= A[i]
      // a * x + turn * b - x * b >= A[i]
      // x * (a - b) >= A[i] - turn * b
      // x >= (A[i] - turn * b) / (a - b)
      cnt += (left + a - b - 1) / (a - b);
    }
    return cnt <= turn;
  };

  int lo = 0, hi = 2e9;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    (can(mid) ? hi : lo) = mid;
  }
  dbg(lo, hi);
  cout << hi << '\n';
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int64_t n, x;
  cin >> n >> x;
  vector<int64_t> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  __int128 lo = 0, hi = numeric_limits<int64_t>::max();
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;

    __int128 w = 0;
    for (auto a : as) {
      w += max<__int128>(0, mid - a);
    }
    (w <= x ? lo : hi) = mid;
  }
  cout << int(lo) << '\n';
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

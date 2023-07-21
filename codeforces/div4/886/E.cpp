#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 =  int64_t;
using u64 = uint64_t;

void solve() {
  int n; 
  u64 c;
  cin >> n >> c;
  vector<int> ss(n);
  for (auto &s : ss) cin >> s;

  auto is_less = [&](__int128 w) -> bool {
    __int128 cur = 0;
    for (auto &s : ss) {
      auto x = __int128(s) + w * 2;
      if ((cur += x * x) >= c) return false;
    }
    return cur < c;
  };

  u64 lo = 0, hi = numeric_limits<i64>::max() + 1;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    (is_less(mid) ? lo : hi) = mid;
  }
  cout << hi << '\n';
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

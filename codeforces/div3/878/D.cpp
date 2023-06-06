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
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  sort(as.begin(), as.end());
  as.erase(unique(as.begin(), as.end()), as.end());

  dbg(as);
  auto can = [&](int x) -> bool {
    auto mid = upper_bound(as.begin(), as.end(), as[0] + 2 * x);
    if (mid == as.end()) return true;
    auto lst = upper_bound(as.begin(), as.end(), *mid + 2 * x);
    if (lst == as.end()) return true;
    return upper_bound(as.begin(), as.end(), *lst + 2 * x) == as.end();
  };

  int lo = -1, hi = *max_element(as.begin(), as.end());
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    (can(mid) ? hi : lo) = mid;
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

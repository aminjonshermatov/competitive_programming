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
  int n, m;
  i64 d;
  cin >> n >> m >> d;

  vector<i64> A(n), B(m);
  for (auto &a : A) cin >> a;
  for (auto &b : B) cin >> b;

  std::sort(A.begin(), A.end());
  std::sort(B.begin(), B.end());

  i64 ans = -1;
  for (auto a : A) {
    auto it = upper_bound(B.begin(), B.end(), a + d);
    if (it == B.begin()) continue;
    it = prev(it);
    if (llabs(a - *it) <= d) ans = max(ans, a + *it);
  }
  cout << ans << '\n';
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

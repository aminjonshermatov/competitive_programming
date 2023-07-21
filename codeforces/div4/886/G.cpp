#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 =  int64_t;
using u64 = uint64_t;

void solve() {
  int n; cin >> n;
  map<i64, i64> by_x, by_y, d, id;
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    i64 x, y;
    cin >> x >> y;
    ans += by_x[x]; ++by_x[x];
    ans += by_y[y]; ++by_y[y];
    ans += d[x - y]; ++d[x - y];
    ans += id[-x - y]; ++id[-x - y];
  }
  cout << ans * 2 << '\n';
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

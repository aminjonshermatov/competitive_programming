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
  i64 n, m; cin >> n >> m;
  vector<i64> as(m);
  for (auto &a : as) cin >> a;

  auto sm = accumulate(as.begin(), as.end(), i64(0));

  cout << max<i64>(0, sm - (m - 1) * n) << '\n';
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using u64 = uint64_t;

void solve() {
  const int n = 64;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  u64 ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    ans <<= 1;
    ans |= as[i];
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

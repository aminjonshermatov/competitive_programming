// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

constexpr int N = 4e6;

void solve() {
  i64 f = 1, s = 2;
  i64 ans = 0;
  while (s <= N) {
    if (s % 2 == 0) ans += s;
    tie(f, s) = tuple(s, f + s);
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

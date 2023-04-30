// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

constexpr int N = 1000 - 1;

i64 sum(int a1, int d, int n) {
  return (i64(2) * a1 + d * (n - 1)) * n / 2;
}

void solve() {
  cout << sum(3, 3, N / 3) + sum(5, 5, N / 5) - sum(3 * 5, 3 * 5, N / (3 * 5)) << '\n';
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

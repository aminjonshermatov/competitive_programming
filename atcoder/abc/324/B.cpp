#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  i64 n;
  cin >> n;
  int x = 0, y = 0;
  while (n > 1 && n % 2 == 0) {
    ++x;
    n /= 2;
  }
  while (n > 1 && n % 3 == 0) {
    ++y;
    n /= 3;
  }
  cout << (n == 1 ? "Yes" : "No") << '\n';
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

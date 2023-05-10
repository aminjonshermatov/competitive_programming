#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

void solve() {
  int n; cin >> n;
  vector<int> B(n);
  for (auto &b : B) cin >> b;
  i64 g = 0;
  i64 l = 0;
  for (int i = 0; i < n; ++i) {
    if (B[i] == -1) {
      l += i + 1;
    } else {
      g += i + 1;
    }
  }
  cout << abs(g - l) << '\n';
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

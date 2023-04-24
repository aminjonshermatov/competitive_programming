// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, t;
  cin >> n >> t;
  vector<int> A(n), B(n);
  for (auto &a : A) cin >> a;
  for (auto &b : B) cin >> b;

  int ans = -1;
  for (int i = 0; i < n; ++i) {
    if (i + A[i] <= t && (ans == -1 || B[i] > B[ans - 1])) {
      ans = i + 1;
    }
  }
  cout << ans << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
}

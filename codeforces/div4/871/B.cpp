// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;
  int cur = 0, ans = 0;
  for (auto a : A) {
    if (a == 0) {
      ++cur;
    } else {
      ans = max(ans, cur);
      cur = 0;
    }
  }
  cout << max(ans, cur) << '\n';
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

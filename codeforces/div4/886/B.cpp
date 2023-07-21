#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<pair<int, int>> as;
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    if (a > 10) continue;
    as.emplace_back(b, i + 1);
  }
  sort(as.rbegin(), as.rend());
  cout << as[0].second << '\n';
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

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
  vector<string> names(n);
  vector<int> ages(n);
  int mn = -1;
  for (int i = 0; i < n; ++i) {
    cin >> names[i] >> ages[i];
    if (mn == -1 || ages[i] < ages[mn]) mn = i;
  }
  for (int i = mn; i < n; ++i) {
    cout << names[i] << '\n';
  }
  for (int i = 0; i < mn; ++i) {
    cout << names[i] << '\n';
  }
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

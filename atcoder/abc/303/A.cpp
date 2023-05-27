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
  string a, b; cin >> a >> b;
  for (int i = 0; i < n; ++i) {
    if (a[i] == b[i]) continue;
    if ((a[i] == '1' && b[i] == 'l') || (a[i] == 'l' && b[i] == '1')) continue ;
    if ((a[i] == '0' && b[i] == 'o') || (a[i] == 'o' && b[i] == '0')) continue ;
    cout << "No\n";
    return;
  }
  cout << "Yes\n";
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

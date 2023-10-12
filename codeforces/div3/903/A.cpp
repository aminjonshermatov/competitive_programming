#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  string x, s;
  cin >> x >> s;
  if (x.find(s) != string::npos) {
    cout << "0\n";
    return;
  }
  for (int i = 1; i <= 15 && x.size() < 1e3; ++i) {
    x = x + x;
    if (x.find(s) != string::npos) {
      cout << i << '\n';
      return;
    }
  }
  cout << "-1\n";
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

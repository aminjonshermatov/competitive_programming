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
  vector<string> ss(n);
  for (auto &s : ss) cin >> s;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      auto ns = ss[i] + ss[j];
      bool ok = true;
      for (int k = 0; ok && k < ns.size() / 2; ++k) {
        ok &= ns[k] == ns[ns.size() - k - 1];
      }
      if (ok) {
        cout << "Yes\n";
        return;
      }
    }
  }
  cout << "No\n";
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

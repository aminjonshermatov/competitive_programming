#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> deg(n, 0);
  for (int i = 0; i < m; ++i) {
    int u, v; cin >> u >> v;
    --u, --v;
    ++deg[u]; ++deg[v];
  }
  for (int i = 0; i < n; ++i) {
    cout << deg[i] << " \n"[i + 1 == n];
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

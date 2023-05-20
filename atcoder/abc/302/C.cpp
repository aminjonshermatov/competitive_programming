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
  vector<string> ws(n);
  for (auto &w : ws) cin >> w;

  vector<int> id(n);
  std::iota(id.begin(), id.end(), 0);
  do {
    bool ok = true;
    for (int i = 0; i + 1 < n && ok; ++i) {
      int diff = 0;
      for (int j = 0; j < m; ++j) {
        diff += ws[id[i]][j] != ws[id[i + 1]][j];
      }
      ok &= diff == 1;
    }
    if (ok) {
      cout << "Yes\n";
      return;
    }
  } while (next_permutation(id.begin(), id.end()));
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

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
  vector<string> g(n);
  for (auto &r : g) cin >> r;

  string s;
  for (int j = 0; j < n; ++j) s.push_back(g[0][j]);
  for (int i = 1; i + 1 < n; ++i) s.push_back(g[i][n - 1]);
  for (int j = n - 1; j >= 0; --j) s.push_back(g[n - 1][j]);
  for (int i = n - 2; i > 0; --i) s.push_back(g[i][0]);
  s.insert(s.begin(), s.back());
  s.pop_back();
  int k = 0;
  for (int j = 0; j < n; ++j) g[0][j] = s[k++];
  for (int i = 1; i + 1 < n; ++i) g[i][n - 1] = s[k++];
  for (int j = n - 1; j >= 0; --j) g[n - 1][j] = s[k++];
  for (int i = n - 2; i > 0; --i) g[i][0] = s[k++];

  for (auto &r : g) {
    cout << r << '\n';
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k, L; cin >> n >> k >> L;
  vector<int> songs;
  for (int i = 0; i < n; ++i) {
    int m, l; cin >> m >> l;
    if (l == L) {
      songs.emplace_back(m);
    }
  }
  sort(songs.rbegin(), songs.rend());
  if (songs.size() < k) {
    cout << -1 << '\n';
    return;
  }
  songs.resize(k);
  cout << accumulate(songs.begin(), songs.end(), 0) << '\n';
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

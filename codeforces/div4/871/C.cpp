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
  vector<int> fst, snd, trd;
  vector<int> M(n);
  for (int i = 0; i < n; ++i) {
    char _1, _2;
    cin >> M[i] >> _1 >> _2;
    if (_1 == '1' && _2 == '1') trd.emplace_back(i);
    if (_1 == '1') fst.emplace_back(i);
    if (_2 == '1') snd.emplace_back(i);
  }
  sort(fst.begin(), fst.end(), [&M](int i, int j) {
    return M[i] < M[j];
  });
  sort(snd.begin(), snd.end(), [&M](int i, int j) {
    return M[i] < M[j];
  });
  sort(trd.begin(), trd.end(), [&M](int i, int j) {
    return M[i] < M[j];
  });
  if (fst.empty() || snd.empty()) {
    cout << -1 << '\n';
    return;
  }
  int ans = M[fst[0]] + M[snd[0]];
  if (fst[0] == snd[0]) ans -= M[fst[0]];
  if (!trd.empty()) ans = min(ans, M[trd[0]]);
  cout << ans << '\n';
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

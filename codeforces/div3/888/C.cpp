#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;
  vector<int> cs(n);
  for (auto &c : cs) cin >> c;

  if (cs[0] == cs[n - 1]) {
    cout << (count(cs.begin(), cs.end(), cs[0]) >= k ? "Yes" : "No") << '\n';
    return;
  }

  vector<int> fst, snd;
  for (int i = 0; i < n; ++i) {
    if (cs[i] == cs[0]) {
      fst.emplace_back(i);
    }
    if (cs[i] == cs[n - 1]) {
      snd.emplace_back(i);
    }
  }

  bool ok = false;
  for (int i = k - 1; i < fst.size(); i += k) {
    ok |= int(snd.end() - lower_bound(snd.begin(), snd.end(), fst[i])) >= k;
  }
  cout << (ok ? "Yes" : "No") << '\n';
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

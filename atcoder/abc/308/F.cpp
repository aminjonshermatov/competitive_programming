#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> ps(n), ls(m), ds(m);
  for (auto &p : ps) cin >> p;
  for (auto &l : ls) cin >> l;
  for (auto &d : ds) cin >> d;

  auto ans = accumulate(ps.begin(), ps.end(), i64(0));
  multiset<int> vals(ps.begin(), ps.end());
  vector<int> ord(m);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int i, int j) { return ds[i] > ds[j]; });
  for (auto i : ord) {
    auto it = vals.lower_bound(ls[i]);
    if (it != vals.end()) {
      ans -= ds[i];
      vals.erase(it);
    }
  }
  cout << ans << '\n';
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

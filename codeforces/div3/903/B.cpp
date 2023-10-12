#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  vector<i64> as(3);
  for (auto &a : as) {
    cin >> a;
  }
  for (int cnt = 0; cnt <= 3; ++cnt) {
    const auto rec = [&](auto &f, vector<i64> cur, int lim) -> bool {
      if (lim >= cnt) {
        return all_of(cur.begin(), cur.end(), [f=cur.front()](auto x) { return x == f; });
      }
      assert(lim <= cnt);
      for (int i = 0; i < cur.size(); ++i) {
        auto ncur = cur;
        ncur.emplace_back(ncur[i] - (ncur[i] / 2));
        ncur[i] /= 2;
        if (f(f, ncur, lim + 1)) {
          return true;
        }
        ncur[i] = cur[i] / 3;
        ncur.back() = cur[i] - ncur[i];
        if (f(f, ncur, lim + 1)) {
          return true;
        }
      }
      return false;
    };
    if (rec(rec, as, 0)) {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
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

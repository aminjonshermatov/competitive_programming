#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  vector<i64> pf(n - 1);
  for (auto &p : pf) {
    cin >> p;
  }

  map<i64, int> cnt{};
  i64 prv = 0;
  for (auto p : pf) {
    if (p < prv) {
      cout << "No\n";
      return;
    }
    ++cnt[p - prv];
    prv = p;
  }

  i64 cnt2 = -1;
  for (auto [d, v] : cnt) {
    if (v == 2 || clamp<i64>(d, 1, n) != d) {
      if (cnt2 != -1) {
        cout << "No\n";
        return;
      }
      cnt2 = d;
    }
  }
  if (cnt2 == -1) {
    cnt2 = i64(n) * (n + 1) / 2 - prv;
    if (clamp<i64>(cnt2, 1, n) == cnt2 && cnt.count(cnt2) == 0) {
      bool used = false;
      for (int x = 1; x <= n; ++x) {
        if (cnt[x] != 1) {
          if (x == cnt2 && !used) {
            used = true;
          } else {
            cout << "No\n";
            return;
          }
        }
      }
      cout << "Yes\n";
      return;
    }
  }
  dbg(cnt2);
  if (--cnt[cnt2] == 0) {
    cnt.erase(cnt2);
  }
  for (int i = 1; i < min<i64>(n + 1, cnt2); ++i) {
    if (clamp<i64>(cnt2 - i, 1, n) == cnt2 - i && cnt[i] == 0 && cnt[cnt2 - i] == 0) {
      bool ok = true;
      ++cnt[i]; ++cnt[cnt2 - i];
      for (int x = 1; x <= n && ok; ++x) {
        if (cnt[x] != 1) {
          ok = false;
        }
      }
      if (ok) {
        cout << "Yes\n";
        return;
      }
      --cnt[i]; --cnt[cnt2 - i];
    }
  }
  cout << "No\n";
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

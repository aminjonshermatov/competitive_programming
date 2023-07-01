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
  int n; cin >> n;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  string s; cin >> s;

  using T = array<int, 3>;
  T suf{0, 0, 0};
  for (int i = n - 1; i >= 0; --i) {
    if (s[i] == 'X') {
      ++suf[as[i]];
    }
  }
  T pref{0, 0, 0};
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'X') {
      --suf[as[i]];
    }

    if (s[i] == 'E') {
      for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
          array<bool, 3> seen{};
          seen.fill(false);
          seen[x] = true;
          seen[y] = true;
          seen[as[i]] = true;
          for (int z = 0; z < 4; ++z) {
            if (z == 3 || !seen[z]) {
              ans += 1ll * z * pref[x] * suf[y];
              break;
            }
          }
        }
      }
    }

    if (s[i] == 'M') {
      ++pref[as[i]];
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

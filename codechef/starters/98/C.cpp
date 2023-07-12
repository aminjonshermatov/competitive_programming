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
  string s; cin >> s;

  auto r = n % 3;
  if (r == 0) {
    array<array<int, 3>, 26> pref{}, suf{};
    for (int i = 0; i < 26; ++i) {
      pref[i].fill(0);
      suf[i].fill(0);
    }
    for (int i = 0; i < n; ++i) {
      ++suf[s[i] - 'a'][i % 3];
    }
    for (int i = 0; i < n; ++i) {
      --suf[s[i] - 'a'][i % 3];
      if (i % 3 == 1) {
        for (int ch = 0; ch < 26; ++ch) {
          if (pref[ch][0] > 0 && suf[ch][2] > 0 && (n - 1) % 3 == 2) {
            cout << "YES\n";
            return;
          }
        }
      }

      ++pref[s[i] - 'a'][i % 3];
    }
  } else if (r == 1) {
    cout << "YES\n";
    return;
  } else if (r == 2) {
    array<int, 26> pref{};
    for (int i = 0; i < 26; ++i) {
      pref.fill(0);
    }
    for (int i = 0; i < n; ++i) {
      if (i % 3 == 1) {
        if (pref[s[i] - 'a'] > 0 && (n - i - 1) % 3 == 0) {
          cout << "YES\n";
          return;
        }
      }
      if (i % 3 == 0) {
        ++pref[s[i] - 'a'];
      }
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

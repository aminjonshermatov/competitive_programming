#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s, t;
  cin >> s >> t;
  array<int, 26> fs{}, ft{};
  fs.fill(0); ft.fill(0);
  int sa = 0, ta = 0;
  for (auto ch : s) {
    if (isalpha(ch)) ++fs[ch - 'a'];
    else ++sa;
  }
  for (auto ch : t) {
    if (isalpha(ch)) ++ft[ch - 'a'];
    else ++ta;
  }

  set<char> atcoder{'a', 't', 'c', 'o', 'd', 'e', 'r'};
  for (int i = 0; i < 26; ++i) {
    if (fs[i] != ft[i]) {
      if (atcoder.count(char('a' + i)) == 0) {
        cout << "No\n";
        return;
      } else {
        auto d = fs[i] - ft[i];
        if (d > 0) {
          if (ta < d) {
            cout << "No\n";
            return;
          }
          ta -= d;
        } else {
          d *= -1;
          if (sa < d) {
            cout << "No\n";
            return;
          }
          sa -= d;
        }
      }
    }
  }
  cout << "Yes\n";
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

// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr inline string_view cf{"codeforces"};

void solve() {
  string s; cin >> s;
  int cnt = 0;
  for (int i = 0; i < s.size(); ++i) {
    cnt += s[i] != cf[i];
  }
  cout << cnt << '\n';
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

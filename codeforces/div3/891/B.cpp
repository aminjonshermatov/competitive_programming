#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  string s; cin >> s;

  const auto n = int(s.size());
  reverse(s.begin(), s.end());
  int last = -1;
  for (int i = 0; i < n; ++i) {
    if (s[i] >= '5') {
      last = i;
    }
  }
  if (last != -1) {
    fill(s.begin(), s.begin() + last + 1, '0');
    int j = last + 1;
    while (j < n && s[j] + 1 >= '5') {
      s[j++] = '0';
    }
    if (j < n) {
      ++s[j];
    } else {
      s.push_back('1');
    }
  }
  reverse(s.begin(), s.end());
  cout << s << '\n';
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

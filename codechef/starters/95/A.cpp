#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  int a = 0, b = 0, ab = 0, o = 0;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    a += s == "A";
    b += s == "B";
    ab += s == "AB";
    o += s == "O";
  }
  cout << o + max(a, b) + ab << '\n';
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

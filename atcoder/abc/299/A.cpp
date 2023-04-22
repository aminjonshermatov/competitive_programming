// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  vector<int> line;
  int star = -1;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '|') {
      line.push_back(i);
    } else if (s[i] == '*') {
      star = i;
    }
  }

  cout << (clamp(star, line[0], line[1]) == star ? "in" : "out") << '\n';
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

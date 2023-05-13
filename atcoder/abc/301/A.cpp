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
  string s; cin >> s;
  auto t = std::count(s.begin(), s.end(), 'T');
  auto a = std::count(s.begin(), s.end(), 'A');
  if (t != a) {
    cout << (t > a ? 'T' : 'A') << '\n';
  } else {
    for (auto ch : s) {
      if (ch == 'T') --t;
      else --a;
      if (t == 0) {
        cout << "T\n";
        return;
      }
      if (a == 0) {
        cout << "A\n";
        return;
      }
    }
  }
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  set<string> good{
    "ACE"s,
    "BDF"s,
    "CEG"s,
    "DFA"s,
    "EGB"s,
    "FAC"s,
    "GBD"s,
  };
  string s; cin >> s;
  cout << (good.count(s) > 0 ? "Yes" : "No") << '\n';
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

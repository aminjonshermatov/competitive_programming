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
  int lo = 1, hi = n;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    cout << "? " << mid << endl;
    int ch; cin >> ch;
    if (ch == 1) hi = mid;
    else lo = mid;
  }
  cout << "! " << lo << endl;
}

bool is_multi = false;

int main() {
  //ios_base::sync_with_stdio(false);
  //cin.tie(nullptr);
  //cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

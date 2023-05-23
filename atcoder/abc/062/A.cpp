#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  array<set<int>, 3> ss{};
  ss[0] = {1,3,5,7,8, 10,12};
  ss[1] = {4,6,9,11};
  ss[2] = {2};
  int x, y; cin >> x >> y;
  for (auto &s : ss) {
    if (s.count(x) > 0 && s.count(y) > 0) {
      cout << "Yes\n";
      return;
    }
  }
  cout << "No\n";
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

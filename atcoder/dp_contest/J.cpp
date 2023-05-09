#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using ld = long double;

void solve() {
  int n; cin >> n;
  int ones = 0, twos = 0, threes = 0;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    ones += x == 1;
    twos += x == 2;
    threes += x == 3;
  }

  vector<vector<vector<ld>>> cache(n + 1, vector<vector<ld>>(n + 1, vector<ld>(n + 1, -1)));
  auto E = [&](auto &E, int _1, int _2, int _3) -> ld {
    if (_1 + _2 + _3 == 0) return 0;
    if (cache[_1][_2][_3] > -.5) return cache[_1][_2][_3];
    ld e = n;
    if (_1 > 0) e += E(E, _1 - 1, _2, _3) * _1;
    if (_2 > 0) e += E(E, _1 + 1, _2 - 1, _3) * _2;
    if (_3 > 0) e += E(E, _1, _2 + 1, _3 - 1) * _3;
    e /= ld(_1 + _2 + _3);
    return cache[_1][_2][_3] = e;
  };
  cout << fixed << setprecision(10) << E(E, ones, twos, threes) << '\n';
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

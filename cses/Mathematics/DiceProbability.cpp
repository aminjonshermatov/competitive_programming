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
  int n, a, b; cin >> n >> a >> b;
  vector<ld> p(n * 6 + 1, 0);
  p[0] = 1;
  for (int _ = 0; _ < n; ++_) {
    vector<ld> np(n * 6 + 1, 0);
    for (int i = 0; i < np.size(); ++i) {
      for (int j = 1; j <= 6; ++j) {
        if (i - j >= 0) {
          np[i] += p[i - j] * 1. / 6;
        }
      }
    }
    p.swap(np);
  }

  ld sm = 0;
  for (int i = a; i <= b; ++i) {
    sm += p[i];
  }
  cout << fixed << setprecision(6) << sm << '\n';
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

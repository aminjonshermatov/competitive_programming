#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int MX = 1e6;

int divs[MX + 1];

void solve() {
  int n; cin >> n;
  memset(divs, 0, sizeof divs);

  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    const int up = (int)sqrt(a);
    for (int d = 1; d <= up; ++d) {
      if (a % d == 0) {
        ++divs[d];
        if (d * d != a) ++divs[a / d];
      }
    }
  }

  for (int i = MX; i >= 1; --i) {
    if (divs[i] > 1) {
      cout << i << '\n';
      return;
    }
  }
  assert(false);
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  auto s = chrono::steady_clock::now();
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  cerr << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - s).count() << '\n';
  return 0;
}
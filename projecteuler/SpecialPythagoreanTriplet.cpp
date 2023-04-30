// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int N = 1'000;

void solve() {
  for (int a = 1; a < N; ++a) {
    for (int b = a + 1; a + b < N; ++b) {
      if (1000 * (a + b) == 500 * 1000 + a * b) {
        auto c = N - a - b;
        assert(a * a + b * b == c * c);
        cout << a * b * c << '\n';
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

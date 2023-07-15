#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

int op(int a, int b) {
  assert(clamp(a, 0, 1) == a);
  assert(clamp(b, 0, 1) == b);
  return (a + b) < 2;
}

int f(string &s, int i, int j) {
  if (i == j) return s[i] - '0';
  return op(f(s, i, j - 1), s[j] - '0');
}

void solve() {
  int n; cin >> n;
  for (int m = 0; m < (1 << n); ++m) {
    string s(n, '0');
    for (auto tmp = m, i = n - 1; tmp > 0; --i, tmp >>= 1) {
      s[i] = char('0' + (tmp & 1));
    }
    dbg(s, f(s, 0, n - 1));
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

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
  vector<int> A(n);
  int s = 0;
  for (auto &a : A) {
    cin >> a;
    s += a;
  }
  if (s % 10 == 0) {
    sort(A.begin(), A.end());
    for (auto x : A) {
      if (x % 10 != 0) {
        s -= x;
        goto ans;
      }
    }
    s = 0;
  }
ans:
  cout << s << '\n';
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

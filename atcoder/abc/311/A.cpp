#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  string s; cin >> s;
  array<int, 3> cnt{};
  for (int i = 0; i < n; ++i) {
    ++cnt[s[i] - 'A'];
    if (all_of(cnt.begin(), cnt.end(), [](auto x) { return x > 0; })) {
      cout << i + 1 << '\n';
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
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

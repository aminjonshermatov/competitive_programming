#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  vector<pair<int, int>> ab(n);
  for (auto &[a, b] : ab) {
    cin >> a >> b;
    b *= -1;
  }

  i64 ans = 0;
  int cur = 0;
  sort(ab.begin(), ab.end());
  vector<bool> on(n, false);
  dbg(ab);
  for (int i = 0, l = 0; i < n; ++i) {
    ans -= ab[i].second;
    on[i] = true;
    ++cur;
    auto x = cur;
    while (l <= i && ab[l].first <= x) {
      cur -= on[l++];
    }
    if (l > i) {
      while (i + 1 < n && ab[i + 1].first == ab[i].first) ++i;
      l = i + 1;
    }
    dbg(l, i);
  }
  cout << ans << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

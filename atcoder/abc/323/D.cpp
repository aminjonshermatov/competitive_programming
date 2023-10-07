#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;
  map<i64, i64> cnt{};
  for (int i = 0; i < n; ++i) {
    i64 s, c;
    cin >> s >> c;
    cnt[s] += c;
  }
  for (auto &[k, v] : cnt) {
    auto c = v / 2;
    cnt[k * 2] += c;
    v -= c * 2;
  }
  int tot = 0;
  for (auto [k, v] : cnt) {
    tot += v > 0;
  }
  cout << tot << '\n';
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

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
  vector<int> as(n);
  for (auto &a : as) cin >> a;

  auto mx = *max_element(as.begin(), as.end());
  vector<int> sp(mx + 1, 0), mu(mx + 1), cnt(mx + 1, 0);
  for (auto a : as) ++cnt[a];
  for (int x = 2; x <= mx; ++x) {
    if (sp[x] > 0) continue;
    for (int y = x; y <= mx; y += x) {
      if (sp[y] > 0) continue;
      sp[y] = x;
    }
  }
  mu[1] = 1;
  for (int x = 2; x <= mx; ++x) {
    if (sp[x / sp[x]] == sp[x]) mu[x] = 0;
    else mu[x] = -mu[x / sp[x]];
  }

  i64 ans = 0;
  for (int x = 1; x <= mx; ++x) {
    i64 c = 0;
    for (int y = x; y <= mx; y += x) {
      c += cnt[y];
    }
    ans += c * (c - 1) / 2 * mu[x];
  }
  cout << ans << '\n';
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

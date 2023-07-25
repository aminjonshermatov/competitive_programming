#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m, k, H; cin >> n >> m >> k >> H;
  vector<int> hs(n);
  for (auto &h : hs) cin >> h;

  int cnt = 0;
  for (auto h : hs) {
    auto d = abs(H - h);
    auto [q, r] = div(d, k);
    cnt += r == 0 && clamp(q, 1, m - 1) == q;
  }
  cout << cnt << '\n';
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

#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int MX_A = 32768;
vector<int> poss;
int cnt[MX_A], ptr = 0;

bool is_pal(int x) {
  int rx = 0;
  for (auto tmp = x; tmp > 0; tmp /= 10) {
    rx = rx * 10 + tmp % 10;
  }
  while (rx > 0 && x > 0) {
    if (rx % 10 != x % 10) {
      return false;
    }
    x /= 10;
    rx /= 10;
  }
  return true;
}

void preprocess() {
  for (int x = 0; x < MX_A; ++x) {
    if (is_pal(x)) {
      poss.emplace_back(x);
    }
  }

  dbg(ptr);
  dbg(poss);
  dbg(poss.size());
}

using i64 = int64_t;

void solve() {
  int n; cin >> n;
  memset(cnt, 0, sizeof(cnt));
  i64 ans = n;
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    for (auto y : poss) {
      auto nx = y ^ x;
      if (clamp(nx, 0, MX_A - 1) == nx) ans += cnt[nx];
    }
    ++cnt[x];
  }
  cout << ans << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  preprocess();
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}

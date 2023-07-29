#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, m; cin >> n >> m;
  vector<int> as(n);
  for (auto &a : as) cin >> a;
  vector<int> bs(m);
  for (auto &b : bs) cin >> b;

  int lo = 0, hi = 1e9 + 10;
  while (hi - lo > 1) {
    auto mid = lo + (hi - lo) / 2;
    int a = 0, b = 0;
    for (auto x : as) {
      a += mid >= x;
    }
    for (auto x : bs) {
      b += mid <= x;
    }
    dbg(mid, a, b);
    (a >= b ? hi : lo) = mid;
  }
  cout << hi << '\n';
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

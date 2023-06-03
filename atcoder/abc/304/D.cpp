#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int w, h; cin >> w >> h;
  int n; cin >> n;
  vector<pair<int, int>> ss(n);
  for (auto &[x, y] : ss) cin >> x >> y;
  int nA; cin >> nA;
  vector<int> as(nA);
  for (auto &a : as) cin >> a;
  int nB; cin >> nB;
  vector<int> bs(nB);
  for (auto &b : bs) cin >> b;

  map<int, vector<int>> byX;
  sort(ss.begin(), ss.end());
  int ptrA = 0;
  int mn = 1e9, mx = -1e9;
  for (int i = 0; i < n; ++i) {

    while (ptrA < nA && ss[i].first > as[ptrA]) {
      ++ptrA;
    }
    byX[ptrA].emplace_back(ss[i].second);
  }
  for (auto &[k, ys] : byX) {
    dbg(ys);
    sort(ys.begin(), ys.end());
    int cur = 0, ptrB = 0;
    for (auto y : ys) {
      while (ptrB < nB && y > bs[ptrB]) {
        mn = min(mn, cur);
        mx = max(mx, cur);
        cur = 0;
        ++ptrB;
      }
      dbg(cur, ptrB, mn, mx);
      ++cur;
    }
    mn = min(mn, cur);
    mx = max(mx, cur);
  }
  cout << mn << ' ' << mx << '\n';
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

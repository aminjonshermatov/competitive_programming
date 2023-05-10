#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int MX = 3e6 + 1;
constexpr int OFFSET = 1e6;

bitset<MX> seen;

void solve() {
  int n; cin >> n;
  cout << max(1, n * 3) << '\n';
//  seen.reset();
//  int y; cin >> y;
//  queue<pair<int, int>> q;
//  if (y != 0) q.emplace(y, OFFSET);
//  seen.set(OFFSET);
//  while (!q.empty()) {
//    auto [yy, x] = q.front(); q.pop();
//    if (yy > 0) {
//      if (!seen[x - 1]) {
//        seen.set(x - 1);
//        q.emplace(yy - 1, x - 1);
//      }
//      if (!seen[x + 2]) {
//        seen.set(x + 2);
//        q.emplace(yy - 1, x + 2);
//      }
//    }
//  }
//  cout << seen.count() << '\n';
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
